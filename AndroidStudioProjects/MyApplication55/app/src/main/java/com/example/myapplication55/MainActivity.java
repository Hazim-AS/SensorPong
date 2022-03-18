package com.example.myapplication55;

import androidx.appcompat.app.AppCompatActivity;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Bundle;
import android.telecom.Call;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    EditText username,password;
    Button btnLogin;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


       username = findViewById(R.id.username);

        final Button button=(Button)findViewById(R.id.button2);
        button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Intent launchactivity= new Intent(MainActivity.this, MainActivity2.class);
                startActivity(launchactivity);
            }
        });
    }
}