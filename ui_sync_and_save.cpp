#include "ui_sync_and_save.h"
#include "QFile"


void ui_sync_and_save::sync()
{
        syncUiVals(sender());//should return ptr of signal caller widget
}

ui_sync_and_save::ui_sync_and_save()
{

}

    void ui_sync_and_save::syncUiVals(QObject *target,uiOp op)
    {

        if(target==NULL)
            return;

       uiItem *item=&uiItems[target];


#ifdef QT_DEBUG
    if(item==NULL || item->valPtr==NULL)
      emit errorMsg("ui ptr invalid , nam:"+target->objectName());
#endif


            switch (item->type){
            case spinBox:{
                QSpinBox*sBox=qobject_cast<QSpinBox*>(target);
                if (sBox != NULL){
                    int*p=(int*)item->valPtr;
                    switch (op){
                    case uiOp::valToUi:
                       switch (item->valueType) {
                       case valType::int_:
                       sBox->setValue(valCorrection(*(int*)item->valPtr,*item,uiOp::valToUi));
                       goto outOfSwitch;
                       case valType::float_:
                       sBox->setValue(valCorrection(*(float*)item->valPtr,*item,uiOp::valToUi));
                       goto outOfSwitch;
                       case valType::double_:
                       sBox->setValue(valCorrection(*(double*)item->valPtr,*item,uiOp::valToUi));
                       goto outOfSwitch;
                       }
                    case uiOp::valFromUi:
                       switch (item->valueType) {
                       case valType::int_:
                       *(int*)item->valPtr=valCorrection(sBox->value(),*item);
                       goto outOfSwitch;
                       case valType::float_:
                       *(float*)item->valPtr=valCorrection(sBox->value(),*item);
                       goto outOfSwitch;
                       case valType::double_:
                       *(double*)item->valPtr=valCorrection(sBox->value(),*item);
                       goto outOfSwitch;
                       }
                     case uiOp::fileFromUi:
                         uiSet->setValue(sBox->objectName(), sBox->value());
                        goto outOfSwitch;
                     case uiOp::fileToUiAndPtr:
                       if(uiSet->contains(sBox->objectName()))
                        sBox->setValue(uiSet->value(sBox->objectName()).toInt());
                        goto outOfSwitch;
                    }
                }}
            case doubleSpinBox:{
                QDoubleSpinBox*dsBox=qobject_cast<QDoubleSpinBox*>(target);
                if (dsBox != NULL){
                    switch (op){
                    case uiOp::valToUi:
                       switch (item->valueType) {
                       case valType::int_:
                       dsBox->setValue(valCorrection(*(int*)item->valPtr,*item,uiOp::valToUi));
                       goto outOfSwitch;
                       case valType::float_:
                       dsBox->setValue(valCorrection(*(float*)item->valPtr,*item,uiOp::valToUi));
                       goto outOfSwitch;
                       case valType::double_:
                       dsBox->setValue(valCorrection(*(double*)item->valPtr,*item,uiOp::valToUi));
                       goto outOfSwitch;
                       }
                    case uiOp::valFromUi:
                       switch (item->valueType) {
                       case valType::int_:
                       *(int*)item->valPtr=valCorrection(dsBox->value(),*item);
                       goto outOfSwitch;
                       case valType::float_:
                       *(float*)item->valPtr=valCorrection(dsBox->value(),*item);
                       goto outOfSwitch;
                       case valType::double_:
                       *(double*)item->valPtr=valCorrection(dsBox->value(),*item);
                       goto outOfSwitch;
                       }
                     case uiOp::fileFromUi:
                         uiSet->setValue(dsBox->objectName(), dsBox->value());
                        goto outOfSwitch;
                     case uiOp::fileToUiAndPtr:
                        if(uiSet->contains(dsBox->objectName()))
                        dsBox->setValue(uiSet->value(dsBox->objectName()).toDouble());
                        goto outOfSwitch;
                    }
                }}
            case checkBox:{
                QCheckBox*cBox=qobject_cast<QCheckBox*>(target);
                if (cBox != NULL){
                    bool*p=(bool*)item->valPtr;
                    switch (op){
                     case uiOp::valToUi:
                        cBox->setChecked(*p);
                        goto outOfSwitch;
                     case uiOp::valFromUi:
                        *p=cBox->isChecked();
                        goto outOfSwitch;
                     case uiOp::fileFromUi:
                         uiSet->setValue(cBox->objectName(), cBox->isChecked());
                        goto outOfSwitch;
                     case uiOp::fileToUiAndPtr:
                        if(uiSet->contains(cBox->objectName()))
                        cBox->setChecked(uiSet->value(cBox->objectName()).toBool());
                        goto outOfSwitch;
                    }
                }}
            case radioButton:{
                QRadioButton*rBut=qobject_cast<QRadioButton*>(target);
                if (rBut != NULL){
                    bool*p=(bool*)item->valPtr;
                    switch (op){
                     case uiOp::valToUi:
                        rBut->setChecked(*p);
                        goto outOfSwitch;
                     case uiOp::valFromUi:
                        *p=rBut->isChecked();
                        goto outOfSwitch;
                     case uiOp::fileFromUi:
                         uiSet->setValue(rBut->objectName(), rBut->isChecked());
                        goto outOfSwitch;
                     case uiOp::fileToUiAndPtr:
                        if(uiSet->contains(rBut->objectName()))
                        rBut->setChecked(uiSet->value(rBut->objectName()).toBool());
                        goto outOfSwitch;
                    }
                }
            }
            case dateTimeEdit:{
                QDateTimeEdit*dtEdit=qobject_cast<QDateTimeEdit*>(target);
                if (dtEdit != NULL){
                    QDateTime*p=(QDateTime*)item->valPtr;
                    switch (op){
                     case uiOp::valToUi:
                        dtEdit->setDateTime(*p);
                        goto outOfSwitch;
                     case uiOp::valFromUi:
                        *p=dtEdit->dateTime();
                        goto outOfSwitch;
                     case uiOp::fileFromUi:
                        uiSet->setValue(dtEdit->objectName(), dtEdit->dateTime());
                        goto outOfSwitch;
                     case uiOp::fileToUiAndPtr:
                        if(uiSet->contains(dtEdit->objectName()))
                        dtEdit->setDateTime(uiSet->value(dtEdit->objectName()).toDateTime());
                        goto outOfSwitch;
                    }
                }}



            case slider:{
                QSlider*sli=qobject_cast<QSlider*>(target);
                if (sli != NULL){

                    switch (op){
                     case uiOp::valToUi:
                        switch (item->valueType) {
                        case valType::int_:
                        sli->setValue(valCorrection(*(int*)item->valPtr,*item,uiOp::valToUi));
                        goto outOfSwitch;
                        case valType::float_:
                        sli->setValue(valCorrection(*(float*)item->valPtr,*item,uiOp::valToUi));
                        goto outOfSwitch;
                        case valType::double_:
                        sli->setValue(valCorrection(*(double*)item->valPtr,*item,uiOp::valToUi));
                        goto outOfSwitch;
                        }
                     case uiOp::valFromUi:

                        switch (item->valueType) {
                        case valType::int_:
                        *(int*)item->valPtr=valCorrection(sli->value(),*item);
                        goto outOfSwitch;
                        case valType::float_:
                        *(float*)item->valPtr=valCorrection(sli->value(),*item);
                        goto outOfSwitch;
                        case valType::double_:
                        *(double*)item->valPtr=valCorrection(sli->value(),*item);
                        goto outOfSwitch;
                        }
                     case uiOp::fileFromUi:
                        uiSet->setValue(sli->objectName(), sli->value());
                        goto outOfSwitch;
                     case uiOp::fileToUiAndPtr:
                        if(uiSet->contains(sli->objectName()))
                        sli->setValue(uiSet->value(sli->objectName()).toInt());
                        goto outOfSwitch;
                    }
                }}


            default:{
                emit errorMsg("ui CaseNotDefined or type and passed ptr mismatch, nam: "+target->objectName());
                return;
            }
            }



            outOfSwitch:




         if(op==uiOp::fileToUiAndPtr){
             syncUiVals(NULL,uiOp::valFromUi);
         }

             if(item->groupIndex!=0){
                 processGroupEvent(item->groupIndex);
                 emit valsUpdated(item->groupIndex);
               }



    }

    void ui_sync_and_save::saveUiValsToFile(QString path)
    {

        uiSet = new QSettings(path,QSettings::IniFormat); //nb mem leak???????
        syncUiVals(NULL,uiOp::fileFromUi);
    }

    bool ui_sync_and_save::loadUiVals(QString path)
    {
        if (QFile::exists(path)){
            uiSet = new QSettings(path,QSettings::IniFormat);  //nb mem leak???????
            syncUiVals(NULL,uiOp::fileToUiAndPtr);
            return 1;
        }else{
            syncUiVals(NULL,uiOp::valFromUi);
            return 0;
        }

    }

    double ui_sync_and_save::valCorrection(double val, uiItem &itm,uiOp op)
    {
            switch (itm.mathOp){
           case noCorrection:{
                return val;
            }
           case add:{
                if(op=valFromUi){
                    return val-itm.mathVal;
                }else{
                    return val+itm.mathVal;
                }
            }
           case rem:{
                if(op=valFromUi){
                    return val+itm.mathVal;
                }else{
                    return val-itm.mathVal;
                }
            }
           case multip:{
                if(op=valFromUi){
                    return val/itm.mathVal;
                }else{
                    return val*itm.mathVal;
                }
            }
           case divide:{
                if(op=valFromUi){
                    return val*itm.mathVal;
                }else{
                    return val/itm.mathVal;
                }
            }
            }

            emit errorMsg("no mat op found");

    }

