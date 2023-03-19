package xyz.kashapovd.work01;

import android.os.Parcel;
import android.os.Parcelable;

public class HistoryItem implements Parcelable {
    //yeah, 2-input system doesn't look good with StringFragment
    //it is problem to fix in lab7
    private String operand1;
    private String operand2;
    private String function;
    private String result;
    public HistoryItem(String operand1, String operand2, String function, String result){
        this.operand1 = operand1;
        this.operand2 = operand2;
        this.function = function;
        this.result = result;
    }

    public HistoryItem(String operand1, String function, String result){
        this.operand1 = operand1;
        this.operand2 = "";
        this.function = function;
        this.result = result;
    }

    public static final Creator<HistoryItem> CREATOR = new Creator<HistoryItem>() {
        @Override
        public HistoryItem createFromParcel(Parcel in) {
            return new HistoryItem(in);
        }

        @Override
        public HistoryItem[] newArray(int size) {
            return new HistoryItem[size];
        }
    };

    public String getTextRepresentation(){
        String textRepresentation;

        if(operand2.equals(""))
            textRepresentation = String.format("We got %1s as result of %2s of %3s",
                    result, function, operand1);
        else
            textRepresentation = String.format("We got %1s as result of %2s of %3s and %4s",
                    result, function, operand1, operand2);
        return textRepresentation;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    protected HistoryItem(Parcel in) {
        operand1 = in.readString();
        operand2 = in.readString();
        function = in.readString();
        result = in.readString();
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(operand1);
        dest.writeString(operand2);
        dest.writeString(function);
        dest.writeString(result);
    }
}
