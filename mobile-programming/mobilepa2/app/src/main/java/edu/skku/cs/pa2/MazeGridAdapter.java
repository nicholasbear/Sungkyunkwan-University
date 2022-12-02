package edu.skku.cs.pa2;

import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.util.DisplayMetrics;
import android.util.Log;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.constraintlayout.widget.ConstraintLayout;

import java.util.ArrayList;

public class MazeGridAdapter extends BaseAdapter {
    private final int[] array;
    private final int[] mypos;
    private final float size;
    private final int[] hint;
    private Context mContext;

    public MazeGridAdapter(Context mContext, float size, int[] array, int[] mypos, int[] hint) {
        this.mContext = mContext;
        this.array = array;
        this.mypos = mypos;
        this.size = size;
        this.hint = hint;
    }

    @Override
    public int getCount() {
        return array.length;
    }

    @Override
    public Object getItem(int i) {
        return array[i];
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        if (view == null) {
            LayoutInflater layoutInflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            view = layoutInflater.inflate(R.layout.grid_sub, viewGroup, false);
        }

        ImageView background = view.findViewById(R.id.white);
        ImageView picture = view.findViewById(R.id.picture);
        get_margin(background, array[i], 350/size, 350/size);
        picture.setImageResource(0);
        if (hint[0] == i && hint[1] != 1){
            picture.setImageResource(R.drawable.hint);
        }
        if (i == size*size - 1){
            picture.setImageResource(R.drawable.goal);
        }
        if (i == mypos[0]){
            picture.setImageResource(R.drawable.user);
            my_position(picture, mypos);
        }
        return view;
    }


    public void get_margin(ImageView view, int value, float width, float height){
        ConstraintLayout.LayoutParams layout = (ConstraintLayout.LayoutParams)view.getLayoutParams();
        DisplayMetrics dm = mContext.getResources().getDisplayMetrics();
        int margin = Math.round(3*dm.density);

        if (value >= 8){
            layout.topMargin = margin;
            height = height -3;
            value = value - 8;
        }
        if (value >= 4){
            layout.leftMargin = margin;
            width = width -3;
            value = value - 4;
        }
        if (value >= 2){
            layout.bottomMargin = margin;
            height = height -3;
            value = value - 2;
        }
        if (value >= 1){
            layout.rightMargin = margin;
            width = width -3;
            value = value - 1;
        }
        view.setLayoutParams(layout);
        view.getLayoutParams().width = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, width, mContext.getResources().getDisplayMetrics());
        view.getLayoutParams().height = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, height, mContext.getResources().getDisplayMetrics());
    }

    public void my_position(ImageView view, int[] pos){
        if(pos[1] == 0){
            view.setRotation(0.0f);
        }
        else if (pos[1] == 1){
            view.setRotation(90.0f);
        }
        else if (pos[1] == 2){
            view.setRotation(180.0f);
        }
        else{
            view.setRotation(270.0f);
        }
    }

}
