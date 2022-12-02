package edu.skku.map.mobile_w9;

import androidx.databinding.BaseObservable;
import androidx.databinding.Bindable;

public class MySimpleViewModel extends BaseObservable{
    private MySimpleModel model;

    public MySimpleViewModel(){
        model = new MySimpleModel(0);
        this.valueString = "Value: 0";
    }

    @Bindable
    private  String valueString = null;

    private String getValueString() {
        return valueString;
    }

    public void setValueString(String valueString){
        this.valueString = valueString;
    }

    public void onAddingButtonClicked(){
        model.addOne();
        this.setValueString("Value: " + model.getValue());
    }
}
