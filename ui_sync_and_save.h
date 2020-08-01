#ifndef UI_SYNC_AND_SAVE_H
#define UI_SYNC_AND_SAVE_H
#include <QObject>
#include "QSettings"
#include "QDoubleSpinBox"
#include "QSpinBox"
#include "QCheckBox"
#include "QRadioButton"
#include "QDateTimeEdit"
#include "QSlider"
#include "typeinfo"

using namespace std;

enum uiOp{
    valToUi,
    valFromUi,
    fileFromUi,
    fileToUi
};

// multip 100 = if setting item x100 , if setting val /100
enum uiItemMath{
   noCorrection,add,rem,multip,divide
};

class ui_sync_and_save : public QObject
{
    Q_OBJECT



public:

    ui_sync_and_save();

    enum uiItems{
    spinBox,doubleSpinBox,checkBox,radioButton,dateTimeEdit,slider
    };
    enum valType{
    int_,float_,double_
    };

    struct uiItem{
        void*valPtr;
        valType valueType;
        uiItems type;
        uiItemMath mathOp;
        double mathVal;
        char groupIndex;
    };
    map<QObject*,uiItem>uiItems;


    /*! Use this function to add ui components for syncing.
   uiItem=ptr to UI component
   setVar=varaible to sync to ui inputs
   groupIndex=Useful for groupin Ui components to call assigned functions of the groups.
   mathOpForUi=to correct for ui component and connected variable format differences ,
   for exampe if variable is 0-1 and ui is 0-100% could use ...,multip,100)
   mathVal=for math correction */
    template <typename S>
    void addUiItem(QObject*uiItem,S&setVar,char groupIndex=0,uiItemMath mathOpForUi=noCorrection,double mathVal=0){
        ui_sync_and_save::uiItem item;
         item.valPtr=&setVar;
         item.mathOp=mathOpForUi;
         item.mathVal=mathVal;
	 item.groupIndex=groupIndex;

         if(typeid (setVar)==typeid(int)){
             item.valueType=valType::int_;
         }else if(typeid (setVar)==typeid(float)){
             item.valueType=valType::float_;
         }else if(typeid (setVar)==typeid(double)){
             item.valueType=valType::double_;
         }


             QDoubleSpinBox*dsBox=qobject_cast<QDoubleSpinBox*>(uiItem);
             if (dsBox != NULL){
                 item.type=doubleSpinBox;
                 connect(dsBox, SIGNAL(valueChanged(double)), this, SLOT(sync()));
                 uiItems[uiItem]=item;
                 return;
             }

             QSpinBox*sBox=qobject_cast<QSpinBox*>(uiItem);
             if (sBox != NULL){
                 item.type=spinBox;
                 connect(sBox, SIGNAL(valueChanged(int)), this, SLOT(sync()));
                 uiItems[uiItem]=item;
                 return;
             }

             QCheckBox*cBox=qobject_cast<QCheckBox*>(uiItem);
             if (cBox != NULL){
                 item.type=checkBox;
                 connect(cBox, SIGNAL(stateChanged(int)), this, SLOT(sync()));
                 uiItems[uiItem]=item;
                 return;
             }
             QRadioButton*rBut=qobject_cast<QRadioButton*>(uiItem);
             if (rBut != NULL){
                 item.type=radioButton;
                 connect(rBut, SIGNAL(pressed()), this, SLOT(sync()));
                 uiItems[uiItem]=item;
                 return;
             }


             QDateTimeEdit*dtEdit=qobject_cast<QDateTimeEdit*>(uiItem);
             if (dtEdit != NULL){
                 item.type=dateTimeEdit;
                 connect(dtEdit, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(sync()));
                 uiItems[uiItem]=item;
                 return;
             }

         QSlider*sli=qobject_cast<QSlider*>(uiItem);
         if (sli != NULL){
         item.type=slider;
         connect(sli, SIGNAL(sliderMoved(int)), this, SLOT(sync()));
         uiItems[uiItem]=item;
         return;
         }


           emit errorMsg("UiItemCastsFailed");

    }




    map<char, std::function<void()>>eventGroups;

    /*! To connect functions to ui item changes via ui item groups.
       Reminder:
         addGroupEvent(num, staticFunc );
         addGroupEvent(num, bind( &MainWin::classFunc, this) );
     */
    void addGroupEvent(char groupIndex, const std::function<void()>& callback){
        if(groupIndex==0)
            return;

        eventGroups[groupIndex]=callback;
    }



    void processGroupEvent(char groupIndex){


            auto iter = eventGroups.find(groupIndex);
            if (iter == eventGroups.end())
            {
               errorMsg("funcPtr not found: group "+n(groupIndex));
               return;
            }

            iter->second();

    }


    void syncUiVal(QObject *target=NULL, uiOp op=uiOp::valFromUi);

    void syncAllUiVals(uiOp op=uiOp::valFromUi);

    QSettings* uiSet;
    void saveUiValsToFile(QString path);
    bool loadUiVals(QString path);



    template <typename Val>
    QString n(Val num,char decimals=2){
       if(typeid(num)==typeid(double)){
           return QString::number(num,'f',decimals);
       }else{
           return QString::number(num);
       }
    }

private:
    double valCorrection(double val,uiItem&itm,uiOp op=valFromUi);
public slots:
    void sync();
signals:
    void errorMsg(QString error);
   // void valsUpdated(char groupIndex);
};

#endif // UI_SYNC_AND_SAVE_H
