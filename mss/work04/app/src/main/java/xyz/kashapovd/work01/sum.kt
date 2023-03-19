package xyz.kashapovd.work01

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.Toast

class sum : Fragment() {

    private lateinit var _button: Button
    private lateinit var _fnum: EditText
    private lateinit var _snum: EditText

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_sum, container, false)
        _button = view.findViewById(R.id.button4)
        _fnum = view.findViewById<EditText>(R.id.editTextTextPersonName3)
        _snum = view.findViewById<EditText>(R.id.editTextTextPersonName4)
        if (this::_fnum.isInitialized and this::_snum.isInitialized and this::_button.isInitialized) {
            _button.setOnClickListener {
                val fnum: String = _fnum.text.trim().toString();
                val snum: String = _snum.text.trim().toString();
                if (!fnum.matches("""^-?[0-9]\d*(\.\d+)?$""".toRegex()) or
                    !snum.matches("""^-?[0-9]\d*(\.\d+)?$""".toRegex())
                ) {
                    Toast.makeText(activity, R.string.calc_error_msg, Toast.LENGTH_SHORT).show()
                    return@setOnClickListener
                }
                val result: Int = fnum.toInt() + snum.toInt()
                addHistoryItem(fnum, snum, "+", result.toString())
                Toast.makeText(activity, result.toString(), Toast.LENGTH_SHORT).show()
            }
        }
        return view
    }
    private fun addHistoryItem(operand1: String, operand2: String, function: String, result: String) {
        val parent = activity as MainActivity?
        parent!!.addToHistory(HistoryItem(operand1, operand2, function, result))
    }
}