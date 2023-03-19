package xyz.kashapovd.work01

import android.annotation.SuppressLint
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.annotation.NonNull
import androidx.recyclerview.widget.RecyclerView

class HistoryListAdapter internal constructor() :
    RecyclerView.Adapter<HistoryListAdapter.HistoryItemViewHolder>() {
    private var history: ArrayList<HistoryItem>

    init {
        history = ArrayList()
    }

    @SuppressLint("NotifyDataSetChanged")
    fun initialize(history: ArrayList<HistoryItem>) {
        this.history = history
        notifyDataSetChanged()
    }

    @NonNull
    override fun onCreateViewHolder(@NonNull viewGroup: ViewGroup, i: Int): HistoryItemViewHolder {
        val view = LayoutInflater.from(viewGroup.context)
            .inflate(R.layout.history_list_item, viewGroup, false)
        return HistoryItemViewHolder(view)
    }

    override fun onBindViewHolder(@NonNull historyItemViewHolder: HistoryItemViewHolder, i: Int) {
        historyItemViewHolder.bind(history[i])
    }

    override fun getItemCount(): Int {
        return history.size
    }

    class HistoryItemViewHolder(itemView: View) :
        RecyclerView.ViewHolder(itemView) {
        private val historyText: TextView
        private val historyButton: Button

        init {
            historyText = itemView.findViewById(R.id.history_text)
            historyButton = itemView.findViewById(R.id.history_button)
        }

        fun bind(historyItem: HistoryItem) {
            historyText.text = historyItem.textRepresentation
            historyButton.setOnClickListener { v: View? ->
                Toast.makeText(
                    historyButton.context,
                    historyItem.textRepresentation,
                    Toast.LENGTH_SHORT
                )
                    .show()
            }
        }
    }
}