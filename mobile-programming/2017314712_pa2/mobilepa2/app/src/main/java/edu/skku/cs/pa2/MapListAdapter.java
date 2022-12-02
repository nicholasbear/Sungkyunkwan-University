package edu.skku.cs.pa2;

import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.TextView;

import java.util.ArrayList;

public class MapListAdapter extends BaseAdapter {
    private ArrayList<Map> map_list;
    private Context mContext;
    public static final String EXT_MAZENAME = "mazename";

    public MapListAdapter(ArrayList<Map> map_list, Context mContext) {
        this.mContext = mContext;
        this.map_list = map_list;
    }

    @Override
    public int getCount() {
        return map_list.size();
    }

    @Override
    public Object getItem(int i) {
        return map_list.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        if (view == null) {
            LayoutInflater layoutInflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            view = layoutInflater.inflate(R.layout.mapselect_sub, viewGroup, false);
        }

        TextView text1 = view.findViewById(R.id.mazename);
        TextView text2 = view.findViewById(R.id.mazesize);
        Button button = view.findViewById(R.id.startbutton);
        text1.setText(map_list.get(i).getName());
        text2.setText(map_list.get(i).getSize());

        button.setOnClickListener(v -> {
            Context context = v.getContext();

            String data = text1.getText().toString();
            Intent intent = new Intent (context, MazeActivity.class);
            intent.putExtra(EXT_MAZENAME, data);
            mContext.startActivity(intent);
        });

        return view;
    }
}
