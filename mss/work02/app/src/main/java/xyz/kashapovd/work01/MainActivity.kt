package xyz.kashapovd.work01

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val button: Button = findViewById(R.id.button)
        val fnum: EditText = findViewById(R.id.editTextTextPersonName)
        val snum: EditText = findViewById(R.id.editTextTextPersonName2)

        button.setOnClickListener {
            if (!fnum.text.trim().toString().matches("""^-?[0-9]\d*(\.\d+)?$""".toRegex()) or
                !snum.text.trim().toString().matches("""^-?[0-9]\d*(\.\d+)?$""".toRegex())
            ) {
                Toast.makeText(this@MainActivity, R.string.calc_error_msg, Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val result: Int = fnum.text.toString().toInt() + snum.text.toString().toInt()
            Toast.makeText(this@MainActivity, result.toString(), Toast.LENGTH_SHORT).show()
        }
    }
}