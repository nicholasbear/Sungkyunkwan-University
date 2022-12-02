package edu.skku.cs.pa2;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class MapSelection extends AppCompatActivity {
    private ListView listview;
    private MapListAdapter maplistAdapter;
    private ArrayList<Map> map_list;

    JSONArray MapArray;
    JSONObject MapObject;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.mapselect);

        Intent intent = getIntent();
        TextView title = findViewById(R.id.username);
        title.setText(intent.getStringExtra("name"));

        OkHttpClient client = new OkHttpClient();
        HttpUrl.Builder urlBuilder = HttpUrl.parse("http://115.145.175.57:10099/maps").newBuilder();
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
                final String myResponse = response.body().string();
                try {
                    MapArray = new JSONArray(myResponse);
                    map_list = new ArrayList<Map>();
                    for(int i = 0 ; i < MapArray.length();i++){
                        MapObject = MapArray.getJSONObject(i);
                        Map temp = new Map();
                        temp.setName(MapObject.getString("name"));
                        temp.setSize(MapObject.getString("size"));
                        map_list.add(temp);
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }

                MapSelection.this.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        listview = findViewById(R.id.mazelist);
                        maplistAdapter = new MapListAdapter(map_list, MapSelection.this);
                        listview.setAdapter(maplistAdapter);
                    }
                });
            }
        });
    }
}