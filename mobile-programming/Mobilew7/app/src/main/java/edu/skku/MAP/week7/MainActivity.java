package edu.skku.MAP.week7;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.HttpUrl;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class MainActivity extends AppCompatActivity {
    Button button;
    TextView textView1, textView2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView1 = findViewById(R.id.textView1);
        textView2 = findViewById(R.id.textView2);
        button = findViewById(R.id.button);


        button.setOnClickListener(view -> {
            OkHttpClient client = new OkHttpClient();


            //String json = gson.toJson(data, DataModel.class);
            String input = textView1.getText().toString();

            HttpUrl.Builder urlBuilder = HttpUrl.parse("http://www.omdbapi.com").newBuilder();
            urlBuilder.addQueryParameter("apikey","d7bf7052");
            urlBuilder.addQueryParameter("t",input);

            String url = urlBuilder.build().toString();

            Request req = new Request.Builder().url(url).build();

            client.newCall(req).enqueue(new Callback() {
                @Override
                public void onFailure(@NonNull Call call, @NonNull IOException e) {
                    e.printStackTrace();
                }

                @Override
                public void onResponse(@NonNull Call call, @NonNull Response response) throws IOException {
                    Gson gson = new GsonBuilder().create();
                    final String myResponse = response.body().string();
                    DataModel data = gson.fromJson(myResponse, DataModel.class);

                    MainActivity.this.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            textView2.setText("Title:"+data.getTitle()+"\nYear:"+data.getYear()+"\nReleased Date:"+data.getReleased_Date()+"\nRuntime:"+data.getRuntime()+"\nGenre:"+data.getGenre()+"\nIMDB Rates:"+data.getIMDB_Rates()+"\nMetascore:"+data.getMetascore());
                        }
                    });

                }
            });

        });
    }
}