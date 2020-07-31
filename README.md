# QtUI-Sync
Synchronizes commonly used GUI elements between UI and in-app variables using line of code per ui-component..
Saving and loading is single line per all ui items.
Without need for separate implementations for ui getters-setter , config file loading , saving code etc.
Connections are established by generating signals for UI value changes.

 Ui items supported:  spinBox,doubleSpinBox,checkBox,radioButton,dateTimeEdit,slider
 Ways of syncing all UI components via single line of code: valToUi, valFromUi,  fileFromUi,   fileToUiAndPtr


    /*! Use this function to add ui components for syncing.
       uiItem=ptr to UI component
       setVar=varaible to sync to ui inputs
       groupIndex=Useful for groupin Ui components to call assigned functions of the groups.
       mathOpForUi=to correct for ui component and connected variable format differences ,
       for exampe if variable is 0-1 and UI format is 0-100% could use ...,multip,100) as UI correction.
       mathVal=for math correction  */
    template <typename S> void addUiItem(QObject*uiItem,S&setVar,char groupIndex=0,uiItemMath mathOpForUi=noCorrection,double mathVal=0){
    

    /*! To connect functions to ui item changes via ui item groups.
      
       Reminder:
         addGroupEvent(num, staticFunc );
         addGroupEvent(num, bind( &MainWin::classFunc, this) );
     */
    void addGroupEvent(char groupIndex, const std::function<void()>& callback)
       

          loadUiVals(path);
          saveUiValsToFile(path);
         
            //connecting signals&slots, for debugging
    connect(&wSync,SIGNAL(errorMsg(QString)),this,SLOT(updateErrorLine(QString)));//for debugging
    connect(&wSync,SIGNAL(valsUpdated(char)),this,SLOT(uiValsUpdated()));//might be not needed in many cases but emits signal on changes of all ui item groups other than 0
   
