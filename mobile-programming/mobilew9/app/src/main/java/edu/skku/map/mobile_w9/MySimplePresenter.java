package edu.skku.map.mobile_w9;

public class MySimplePresenter implements MySimpleContract.ContractForPresenter,
        MySimpleContract.ContractForModel.OnValueChangedListener{
    private MySimpleContract.ContractForView view;
    private MySimpleContract.ContractForModel model;
    public MySimplePresenter(MySimpleContract.ContractForView view,
                             MySimpleContract.ContractForModel model){
        this.view = view;
        this.model = model;
    }
    @Override
    public void onAddButtonTouched() {
        model.addOne(this);
    }
    @Override
    public void onChanged() {
        if(view != null) view.displayValue(model.getValue());
    }
}