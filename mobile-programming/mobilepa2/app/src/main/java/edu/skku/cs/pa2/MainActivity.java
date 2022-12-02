package edu.skku.cs.pa2;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

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

class Success{
    private String success;

    public String getSuccess() {
        return success;
    }

    public void setSuccess(String success) {
        this.success = success;
    }
}

public class MainActivity extends AppCompatActivity {

    Button button;
    TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = findViewById(R.id.editText);
        button = findViewById(R.id.button);

        button.setOnClickListener(view -> {
            OkHttpClient client = new OkHttpClient();

            HttpUrl.Builder urlBuilder = HttpUrl.parse("http://115.145.175.57:10099/users").newBuilder();
            DataModel data = new DataModel();
            data.setUsername(textView.getText().toString());
            Gson gson = new Gson();
            String json = gson.toJson(data,DataModel.class);

            String url = urlBuilder.build().toString();
            Request req = new Request.Builder()
                    .url(url)
                    .post(RequestBody.create(MediaType.parse("application/json"),json))
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
                    Success tf = gson.fromJson(myResponse, Success.class);


                    MainActivity.this.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            if(tf.getSuccess().equals("true"))
                            {
                                Intent intent = new Intent(MainActivity.this, MapSelection.class);
                                intent.putExtra("name",textView.getText().toString());
                                startActivity(intent);
                            }
                            else
                            {
                                Toast.makeText(getApplicationContext(),"Wrong User Name",Toast.LENGTH_SHORT).show();
                            }
                        }
                    });
                }
            });
        });

    }
}
