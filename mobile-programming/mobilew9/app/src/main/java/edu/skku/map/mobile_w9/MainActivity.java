package edu.skku.map.mobile_w9;

import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;

import android.os.Bundle;
import android.widget.Button;

import edu.skku.map.mobile_w9.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ActivityMainBinding activityMainBinding =
                DataBindingUtil.setContentView(this, R.layout.activity_main);
        activityMainBinding.setMySimpleViewModel(new MySimpleViewModel());
        activityMainBinding.executePendingBindings();
    }

}