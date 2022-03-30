package com.example.myapplication55;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatActivity;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Bundle;
import android.telecom.Call;
import android.view.View;
import android.widget.Button;

import android.os.Bundle;

public class MainActivity2 extends AppCompatActivity {

      @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_main2);

            final Button button=(Button)findViewById(R.id.lancer_une_partie);
            button.setOnClickListener(new View.OnClickListener()
            {
                @Override
                public void onClick(View v)
                {
                    Intent launchactivity= new Intent(MainActivity2.this, MainActivity3.class);
                    startActivity(launchactivity);
                }
            });
        }
    }

