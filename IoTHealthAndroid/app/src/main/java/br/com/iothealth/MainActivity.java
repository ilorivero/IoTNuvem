package br.com.iothealth;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.speech.tts.TextToSpeech;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.Locale;

public class MainActivity extends AppCompatActivity implements TextToSpeech.OnInitListener {
    String TAG = "IoTHealth", falar="";
    TextView txtBpm, txtSpO2, txtTemp;
    TextToSpeech tts;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tts=new TextToSpeech(this, this) ;

        txtBpm = findViewById(R.id.txtBPM);
        txtSpO2 = findViewById(R.id.txtSpO2);
        txtTemp = findViewById(R.id.txtTemp);

        DatabaseReference mRootRef = FirebaseDatabase.getInstance().getReference();
        DatabaseReference temperatura = mRootRef.child("sensor/Temperatura");
        DatabaseReference SpO2 = mRootRef.child("sensor/SpO2");
        DatabaseReference BPM = mRootRef.child("sensor/BPM");

        temperatura.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String value = dataSnapshot.getValue(String.class);
                txtTemp.setText(value);
                Log.d(TAG, "Valor Temperatura: " + value);
            }
            @Override
            public void onCancelled(DatabaseError error) {
                Log.w(TAG, "Falha ao ler o valor.", error.toException());
            }
        });
        BPM.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String value = dataSnapshot.getValue(String.class);
                txtBpm.setText(value);
                Log.d(TAG, "Valor Batimentos/Minuto: " + value);
            }
            @Override
            public void onCancelled(DatabaseError error) {
                Log.w(TAG, "Falha ao ler o valor.", error.toException());
            }
        });
        SpO2.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                String value = dataSnapshot.getValue(String.class);
                txtSpO2.setText(value);
                Log.d(TAG, "Valor da Saturação SpO2: " + value);
            }
            @Override
            public void onCancelled(DatabaseError error) {
                Log.w(TAG, "Falha ao ler o valor.", error.toException());
            }
        });

    }

    public void onClick (View v){
        switch (v.getId()) {
            case R.id.btnFalarDados:
                falar = "A frequência cardíaca de " + txtBpm.getText().toString() + " batimentos por minuto";
                falar += " com saturação de oxigênio de " + txtSpO2.getText().toString() + " porcento";
                falar += ", com temperatura de " + txtTemp.getText().toString() + " graus celsius";
                tts.speak(falar, TextToSpeech.QUEUE_FLUSH, null);
                break;
            case R.id.txtTemp:
                falar = " A temperatura é de " + txtTemp.getText().toString() + " graus celsius";
                tts.speak(falar, TextToSpeech.QUEUE_FLUSH, null);
                break;
            case R.id.txtBPM:
                falar = " A frequência cardíaca de " + txtBpm.getText().toString() + " batimentos por minuto";
                tts.speak(falar, TextToSpeech.QUEUE_FLUSH, null);
                break;
            case R.id.txtSpO2:
                falar = " A saturação de oxigênio de " + txtSpO2.getText().toString() + " porcento";
                tts.speak(falar, TextToSpeech.QUEUE_FLUSH, null);
                break;
        }

    }

    public void onPause(){
        if(tts !=null){
            tts.stop();
            tts.shutdown();
        }
        super.onPause();
    }

    public void onDestroy(){
        if(tts !=null){
            tts.stop();
            tts.shutdown();
        }
        super.onDestroy();
    }

    @Override
    public void onInit(int i) {
        Locale localeBR = new Locale("pt","br");
        tts.setLanguage(localeBR);
    }
}