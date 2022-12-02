# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and child states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed child
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        childGameState = currentGameState.getPacmanNextState(action)
        newPos = childGameState.getPacmanPosition()
        newFood = childGameState.getFood()
        newGhostStates = childGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]

        "*** YOUR CODE HERE ***"
        #크면 좋음 고스트멀리있음
        ghost_dist = float('inf')
        for ghost in newGhostStates:
            ghost_dist = min(ghost_dist, manhattanDistance(newPos, ghost.getPosition()))
            if manhattanDistance(newPos, ghost.getPosition()) < 2 :
                return -float('inf')
        
        #크면 안좋음 음식멀리있음
        newFood = newFood.asList()
        food_dist = float('inf')
        for food in newFood:
            food_dist = min(food_dist, manhattanDistance(newPos, food))
        
        #print(food_dist)
        return childGameState.getScore() + 1/food_dist - 1/ghost_dist

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.getNextState(agentIndex, action):
        Returns the child game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        def minimax(agent, depth, gameState):
            if gameState.isLose() or gameState.isWin() or depth == self.depth:
                return self.evaluationFunction(gameState)
            if agent == 0:  #pacman은 최대
                return max(minimax(1, depth, gameState.getNextState(agent, nextState)) for nextState in gameState.getLegalActions(agent))
            else:  # ghost는 최소
                agentIndex = agent + 1
                if gameState.getNumAgents() == agentIndex: #한바퀴 다돔
                    agentIndex = 0
                if agentIndex == 0:
                    depth += 1
                return min(minimax(agentIndex, depth, gameState.getNextState(agent, nextState)) for nextState in gameState.getLegalActions(agent))

        temp = float("-inf")
        action = Directions.STOP
        for move in gameState.getLegalActions(0):
            result = minimax(1, 0, gameState.getNextState(0, move))
            if result > temp:
                temp = result
                action = move

        return action

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        def pacman_prune(agent, depth, gameState, a, b): #max가 가지는 최솟값
            v = float("-inf")
            for nextState in gameState.getLegalActions(agent):
                v = max(v, alphabetaprune(1, depth, gameState.getNextState(agent, nextState), a, b))
                if v > b:
                    return v
                a = max(a, v)
            return v

        def ghost_prune(agent, depth, gameState, a, b): #min이 가지는 최대값
            v = float("inf")

            agentIndex = agent + 1
            if gameState.getNumAgents() == agentIndex:
                agentIndex = 0
            if agentIndex == 0:
                depth += 1

            for nextState in gameState.getLegalActions(agent):
                v = min(v, alphabetaprune(agentIndex, depth, gameState.getNextState(agent, nextState), a, b))
                if v < a:
                    return v
                b = min(b, v)
            return v

        def alphabetaprune(agent, depth, gameState, a, b):
            if gameState.isLose() or gameState.isWin() or depth == self.depth:
                return self.evaluationFunction(gameState)

            if agent == 0:
                return pacman_prune(agent, depth, gameState, a, b)
            else:
                return ghost_prune(agent, depth, gameState, a, b)

        temp = float("-inf")
        action = Directions.STOP
        a = float("-inf")
        b = float("inf")
        for move in gameState.getLegalActions(0):
            result = alphabetaprune(1, 0, gameState.getNextState(0, move), a, b)
            if result > temp:
                temp = result
                action = move
            a = max(a, result)

        return action

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        def expectimax(agent, depth, gameState):
            if gameState.isLose() or gameState.isWin() or depth == self.depth:
                return self.evaluationFunction(gameState)
            if agent == 0:  #pacman은 최대
                return max(expectimax(1, depth, gameState.getNextState(agent, nextState)) for nextState in gameState.getLegalActions(agent))
            else:  # ghost는 최소
                agentIndex = agent + 1
                if gameState.getNumAgents() == agentIndex: #한바퀴 다돔
                    agentIndex = 0
                if agentIndex == 0:
                    depth += 1
                return sum(expectimax(agentIndex, depth, gameState.getNextState(agent, nextState)) for nextState in gameState.getLegalActions(agent)) / float(len(gameState.getLegalActions(agent)))

        temp = float("-inf")
        action = Directions.STOP
        for move in gameState.getLegalActions(0):
            result = expectimax(1, 0, gameState.getNextState(0, move))
            if result > temp:
                temp = result
                action = move

        return action

def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    1번문제에서 캡슐수를 로직에 추가함, 고스트 거리 다 더함
    """
    "*** YOUR CODE HERE ***"
    newPos = currentGameState.getPacmanPosition()
    newFood = currentGameState.getFood()
    newGhostStates = currentGameState.getGhostStates()

    "*** YOUR CODE HERE ***"
    if currentGameState.isWin():
        return float("inf")
    elif currentGameState.isLose():
        return -float("inf")
    
    #크면 좋음 고스트멀리있음
    ghost_dist = 0
    for ghost in newGhostStates:
        ghost_dist += manhattanDistance(newPos, ghost.getPosition())
        if manhattanDistance(newPos, ghost.getPosition()) < 2 :
            return -float('inf')
    
    #크면 안좋음 음식멀리있음
    newFood = newFood.asList()
    food_dist = float('inf')
    for food in newFood:
        food_dist = min(food_dist, manhattanDistance(newPos, food))
    
    #캡슐 수 크면 안좋음
    Capsule = currentGameState.getCapsules()
    
    #print(food_dist)
    return currentGameState.getScore() + float(1/food_dist) - float(1/ghost_dist) - len(Capsule)

# Abbreviation
better = betterEvaluationFunction
