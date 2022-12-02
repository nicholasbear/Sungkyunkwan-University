package edu.skku.cs.pa2;

import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.GridView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import org.w3c.dom.Text;

import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

class MazeStructure {
    private String maze;

    public String getMaze() {
        return maze;
    }

    public void setMaze(String maze) {
        this.maze = maze;
    }
}

public class MazeActivity extends AppCompatActivity {
    private GridView gridview;
    private MazeGridAdapter mazegridAdapter;
    private int[] maze;
    private int[] mypos;
    private int[] hint;
    private int turn_val;
    private int size;
    private int check_hint;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mazeactivity);
        Button right_btn = findViewById(R.id.right);
        Button left_btn = findViewById(R.id.left);
        Button up_btn = findViewById(R.id.up);
        Button down_btn = findViewById(R.id.down);
        Button hint_btn = findViewById(R.id.hint);
        TextView turn = findViewById(R.id.turn);
        turn_val = 0;
        check_hint = 0;

        Intent intent = getIntent();
        String temp = intent.getStringExtra(MapListAdapter.EXT_MAZENAME);

        OkHttpClient client = new OkHttpClient();
        HttpUrl.Builder urlBuilder = HttpUrl.parse("http://115.145.175.57:10099/maze/map").newBuilder();
        urlBuilder.addQueryParameter("name",temp);


        String url = urlBuilder.build().toString();
        Request req = new Request.Builder()
                .url(url)
                .build();

        client.newCall(req).enqueue(new Callback() {
            @Override
            public void onFailure(@NonNull Call call, @NonNull IOException e) {
                e.printStackTrace();
            }
            @Override
            public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                Gson gson = new GsonBuilder().create();
                final String myResponse = response.body().string();
                MazeStructure structure_tmp = gson.fromJson(myResponse, MazeStructure.class);
                String temp = structure_tmp.getMaze().split("\n")[0];
                size = Integer.parseInt(temp);
                maze = new int[size * size];
                for(int i = 0 ; i < size; i++){
                    for(int j =0 ; j < size; j++){
                        maze[i*size+j] = Integer.parseInt(structure_tmp.getMaze().split("\n")[i+1].split(" ")[j]);
                    }
                }
                mypos = new int[2];
                hint = new int[2];
                mypos[0] = 0; //위치
                mypos[1] = 0; //모습
                hint[0] = -1;
                hint[1] = 0;

                MazeActivity.this.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        gridview = findViewById(R.id.gridview);
                        gridview.setNumColumns(size);
                        mazegridAdapter = new MazeGridAdapter(getApplicationContext(),(float)size,maze,mypos,hint);
                        gridview.setAdapter(mazegridAdapter);

                        right_btn.setOnClickListener(view -> {
                            if (Right_Ok(mypos[0], size, maze) == 1) {
                                mypos[0] += 1;
                                mypos[1] = 1;
                                turn_val = turn_val + 1;
                                turn.setText("Turn: " + Integer.toString(turn_val));
                            }
                            if (hint[1] == 0 && hint[0] == mypos[0])
                                hint[1] = 1;
                            if (mypos[0] == size*size - 1)
                                Toast.makeText(getApplicationContext(),"Finish!",Toast.LENGTH_SHORT).show();
                            mazegridAdapter.notifyDataSetChanged();
                        });

                        left_btn.setOnClickListener(view -> {
                            if (Left_Ok(mypos[0], size, maze) == 1){
                                    mypos[0] -= 1;
                                    mypos[1] = 3;
                                    turn_val = turn_val + 1;
                                    turn.setText("Turn: " + Integer.toString(turn_val));
                            }
                            if (hint[1] == 0 && hint[0] == mypos[0])
                                hint[1] = 1;
                            if (mypos[0] == size*size - 1)
                                Toast.makeText(getApplicationContext(),"Finish!",Toast.LENGTH_SHORT).show();
                            mazegridAdapter.notifyDataSetChanged();
                        });

                        up_btn.setOnClickListener(view -> {
                            if (Up_Ok(mypos[0], size, maze) == 1){
                                mypos[0] -= size;
                                mypos[1] = 0;
                                turn_val = turn_val + 1;
                                turn.setText("Turn: " + Integer.toString(turn_val));
                            }
                            if (hint[1] == 0 && hint[0] == mypos[0])
                                hint[1] = 1;
                            if (mypos[0] == size*size - 1)
                                Toast.makeText(getApplicationContext(),"Finish!",Toast.LENGTH_SHORT).show();
                            mazegridAdapter.notifyDataSetChanged();
                        });

                        down_btn.setOnClickListener(view -> {
                            if (Down_Ok(mypos[0], size, maze) == 1){
                                mypos[0] += size;
                                mypos[1] = 2;
                                turn_val = turn_val + 1;
                                turn.setText("Turn: " + Integer.toString(turn_val));
                            }
                            if (hint[1] == 0 && hint[0] == mypos[0])
                                hint[1] = 1;
                            if (mypos[0] == size*size - 1)
                                Toast.makeText(getApplicationContext(),"Finish!",Toast.LENGTH_SHORT).show();
                            mazegridAdapter.notifyDataSetChanged();
                        });

                        hint_btn.setOnClickListener(view -> {
                            if (check_hint == 0){
                                int[] check = new int[size*size];
                                for(int i = 0; i < size*size ; i++)
                                {
                                    check[i] = 0;
                                }

                                Queue<Integer> queue = new LinkedList<>();
                                queue.add(size*size - 1);
                                while (!queue.isEmpty()) {
                                    int main = queue.poll();
                                    int temp;
                                    Log.d("hint","main is" + Integer.toString(main));
                                    if (Left_Ok(main, size, maze) == 1) {
                                        temp = main - 1;
                                        if (temp == mypos[0]) {
                                            hint[0] = temp + 1;
                                            break;
                                        }
                                        if (check[temp] == 0) {
                                            check[temp] = 1;
                                            queue.add(temp);
                                        }
                                    }
                                    if (Right_Ok(main, size, maze) == 1) {
                                        temp = main + 1;
                                        if (temp == mypos[0]) {
                                            hint[0] = temp - 1;
                                            break;
                                        }
                                        if (check[temp] == 0) {
                                            check[temp] = 1;
                                            queue.add(temp);
                                        }
                                    }
                                    if (Up_Ok(main, size, maze) == 1) {
                                        temp = main - size;
                                        if (temp == mypos[0]) {
                                            hint[0] = temp + size;
                                            break;
                                        }
                                        if (check[temp] == 0) {
                                            check[temp] = 1;
                                            queue.add(temp);
                                        }
                                    }
                                    if (Down_Ok(main, size, maze) == 1) {
                                        temp = main + size;
                                        if (temp == mypos[0]) {
                                            hint[0] = temp - size;
                                            break;
                                        }
                                        if (check[temp] == 0) {
                                            check[temp] = 1;
                                            queue.add(temp);
                                        }
                                    }
                                }
                                check_hint = 1;
                                Log.d("hint","hint is"+ Integer.toString(hint[0]));
                                mazegridAdapter.notifyDataSetChanged();
                            }
                        });

                    }
                });


            }
        });
    }

    public int Left_Ok(int mypos, int size, int[] maze){
        int temp = maze[mypos];
        if (temp >= 8)
            temp = temp -8;
        if (temp < 4){
            return 1;
        }
        return 0;
    }

    public int Right_Ok(int mypos, int size, int[] maze){
        if (maze[mypos] % 2 == 0){
            return 1;
        }
        return 0;
    }

    public int Up_Ok(int mypos, int size, int[] maze){
        int temp = maze[mypos];
        if (temp < 8){
            return 1;
        }
        return 0;
    }

    public int Down_Ok(int mypos, int size, int[] maze){
        int temp = maze[mypos];
        if (temp >= 8)
            temp = temp - 8;
        if (temp >= 4)
            temp = temp -4;
        if (temp < 2){
            return 1;
        }
        return 0;
    }
}