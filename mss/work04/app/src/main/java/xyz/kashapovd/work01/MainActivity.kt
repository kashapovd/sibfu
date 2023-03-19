package xyz.kashapovd.work01

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import android.widget.Button
import android.widget.FrameLayout
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment

class MainActivity : AppCompatActivity() {

    var fragmentSlot: FrameLayout? = null
    private var state = 0
    private val Sum_fragment = 1
    private val Multi_fragment = 2
    private lateinit var history: ArrayList<HistoryItem>
    private val HISTORY_KEY = "history"

    @SuppressLint("MissingInflatedId")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        history = ArrayList()
        fragmentSlot = findViewById(R.id.fragment_main);
        val button: Button = findViewById(R.id.button2)
        if (fragmentSlot != null) {
            setSumFragment()
            button.setOnClickListener { v -> switchFragment() }
        }
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu_main, menu);
        return super.onCreateOptionsMenu(menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.itemId) {
            R.id.open_history -> {
                val intent = Intent(this, HistoryListActivity::class.java)
                intent.putParcelableArrayListExtra(HISTORY_KEY, history)
                startActivity(intent)
            }
        }
        return super.onOptionsItemSelected(item)
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

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        outState.putParcelableArrayList(HISTORY_KEY, history)
    }

    fun addToHistory(newItem: HistoryItem?) {
        history.add(newItem!!)
    }
}