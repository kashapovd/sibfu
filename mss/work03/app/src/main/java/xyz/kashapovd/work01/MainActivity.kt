package xyz.kashapovd.work01

import android.annotation.SuppressLint
import android.os.Bundle
import android.widget.Button
import android.widget.FrameLayout
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment

class MainActivity : AppCompatActivity() {

    var fragmentSlot: FrameLayout? = null
    private var state = 0
    private val Sum_fragment = 1
    private val Multi_fragment = 2

    @SuppressLint("MissingInflatedId")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        fragmentSlot = findViewById(R.id.fragment_main);
        val button: Button = findViewById(R.id.button2)
        if (fragmentSlot != null) {
            setSumFragment()
            button.setOnClickListener { v -> switchFragment() }
        }
    }

    private fun setFragment(fragment: Fragment){
        val fram = supportFragmentManager.beginTransaction()
        fram.replace(R.id.fragment_main, fragment)
        fram.commit()
    }

    private fun setSumFragment() {
        setFragment(sum())
        state = Sum_fragment
    }


    private fun setMulFragment() {
        setFragment(mul())
        state = Multi_fragment
    }

    private fun switchFragment() {
        if (state === Sum_fragment) {
            setMulFragment()
        } else if (state === Multi_fragment) {
            setSumFragment()
        }
    }
}