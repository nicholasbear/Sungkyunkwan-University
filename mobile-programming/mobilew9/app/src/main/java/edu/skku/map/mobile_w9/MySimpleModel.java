package edu.skku.map.mobile_w9;

public class MySimpleModel{
    private int value;

    public MySimpleModel(int initialValue){
        this.value = initialValue;
    }

    public int getValue(){
        return this.value;
    }

    public void addOne(){
        this.value += 1;
    }
}