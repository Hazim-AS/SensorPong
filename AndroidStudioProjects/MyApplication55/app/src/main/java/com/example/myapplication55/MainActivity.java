package com.example.myapplication55;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    EditText username,password;
    Button btnLogin;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main3);


       username = findViewById(R.id.username3);
       password = findViewById(R.id.Password);
       btnLogin = findViewById(R.id.button2);
       String correct_username = "admin";
       String correct_password = "kais";
        //final Button button=(Button)findViewById(R.id.button2);
        btnLogin.setOnClickListener(new View.OnClickListener() {
                                        @Override
                                        public void onClick(View v) {
                                            if (username.getText().length() >0 && password.getText().length() > 0) {
                                                //String toastMessage = "Username: " + email.getText().toString() + ", Password: " + mdp.getText().toString();
                                                // Toast.makeText(getApplicationContext(), toastMessage, Toast.LENGTH_SHORT).show();
                                                Intent valider = new Intent(MainActivity.this, MainActivity2.class);
                                                startActivity(valider);

                                            }



                                            else {
                                                String toastMessage = "Pas de mdp+iden ";
                                                Toast.makeText(getApplicationContext(), toastMessage, Toast.LENGTH_SHORT).show();
                                            }
                                    }
//            @Override
//            public void onClick(View v) {
//
//                Intent launchactivity = new Intent(MainActivity.this, MainActivity2.class);
//                startActivity(launchactivity);
//                if (TextUtils.isEmpty(username.getText().toString()) || TextUtils.isEmpty(password.getText().toString())) {
//                    Toast.makeText(MainActivity.this, "Empty data provided", Toast.LENGTH_LONG).show();
//
//                } else if (username.getText().toString().equals(correct_username)) {
//
//                    if (password.getText().toString().equals(correct_password)) {
//                        Toast.makeText(MainActivity.this, "Successful Login", Toast.LENGTH_LONG).show();
//                    } else {
//
//                        Toast.makeText(MainActivity.this, "Invalid Username/Password", Toast.LENGTH_LONG).show();
//                    }
//
//                } else {
//                    Toast.makeText(MainActivity.this, "Invalid Username/Password", Toast.LENGTH_LONG).show();
//                }
     //       }
        });
    }
}
