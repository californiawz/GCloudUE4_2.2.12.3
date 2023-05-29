/**************************************************

**** @file:     pixuilib_external_bp_call.cpp

**** @brief:    

**** @author:   tianzelei

**** @date:     2021/11/09

**** @group:    PixUI

**** @copyright: Copyright 2021 PixUI. All Rights Reserved.

***************************************************/


#if 0	//be used static loader;  set 1 for static loaded; 0 for dynamic loaded
#define PX_LIB_STATIC_LOADER
#endif	//

//template head file
#include "hf_loadlib_template.h"		//do not delete this!!!!!!!!!!!!!!!!!!!


//for set your library version
DF_PX_LIB_VERSION(0.1.0)



/****************************************add your include head file********************************************/

#include "PixExtBpCall.h"

#include <string>

/**************************************************************************************************************/






/*******************************************add your code here*************************************************/

pixui::PxLibValue CallBPFun(const char* psz_bp_path, const char* psz_fun_name, pixui::PxLibParams* p_args)
{
	pixui::PxLibValue px_lib_val =  PixExtBpCall::CappBPClassFun(UTF8_TO_TCHAR(psz_bp_path), UTF8_TO_TCHAR(psz_fun_name), p_args);

	return px_lib_val;
}

pixui::PxLibValue CallBPCFun(const char* psz_bp_path, const char* psz_fun_name, pixui::PxLibParams* p_args)
{
	pixui::PxLibValue px_lib_val = PixExtBpCall::CappCBPClassFun(UTF8_TO_TCHAR(psz_bp_path), UTF8_TO_TCHAR(psz_fun_name), p_args);

	return px_lib_val;
}


/**************************************************************************************************************/






/*************************************set your library namespace here******************************************/
DF_PX_LIB_START(UE4_PixUI)				//do not delete this!!!!!!!!!!!!!!!!!!!


/**************************************************************************************************************/






/*******************************************add your delegate here*********************************************/
DF_PX_LIB_DELEGATE_PROCESS_START()   //do not delete this!!!!!!!!!!!!!!!!!!!
/*
add your delegate code to here
ps:static delegate need C++17 support,
void CustomFun();   //OK

static void CustomFun();   //need C++17 support,
*/


/*
// sample----------------------------------------------------------------
void custom_delegate(int a, float b, const char* msg)
{
	//DF_PX_LIB_DELEGATE_CALL( delegate name, params... );
	DF_PX_LIB_DELEGATE_CALL(custom_delegate, a, b, msg);
}

int custom_delegate_ret(int a, float b, const char* msg)
{
	//DF_PX_LIB_DELEGATE_CALL_RET( RET_TYPE, delegate name, params... );
	DF_PX_LIB_DELEGATE_CALL_RET(int, custom_delegate_ret, a, b, msg);
	return 0;
}
// sample----------------------------------------------------------------
*/



DF_PX_LIB_DELEGATE_PROCESS_END()	//do not delete this!!!!!!!!!!!!!!!!!!!
/**************************************************************************************************************/






/**********************************add your code here when library loading*************************************/
DF_PX_LIB_INIT_START()      //do not delete this!!!!!!!!!!!!!!!!!!!
{
    //add your code here when library loading
	
	
}
DF_PX_LIB_INIT_END()        //do not delete this!!!!!!!!!!!!!!!!!!!
/**************************************************************************************************************/






/**********************************add your function here for register****************************************/
DF_PX_LIB_INFOR_REG_START()			//do not delete this!!!!!!!!!!!!!!!!!!!
{
	//register your function
	//DF_PX_LIB_REG_FUN( custom function );

	//add your code here for register function
	DF_PX_LIB_REG_FUN(CallBPFun);
	DF_PX_LIB_REG_FUN(CallBPCFun);

	//register your delegate
	//DF_PX_LIB_REG_DELEGATE( custom delegate );

	//add your code here for register delegate
	/*
	// sample----------------------------------------------------------------
	DF_PX_LIB_REG_DELEGATE(custom_delegate);
	DF_PX_LIB_REG_DELEGATE(custom_delegate_ret);
	// sample----------------------------------------------------------------
	*/

}
DF_PX_LIB_INFOR_REG_END()			//do not delete this!!!!!!!!!!!!!!!!!!!
/**************************************************************************************************************/






/**************************************add your delegate here for set******************************************/
DF_PX_LIB_DELEGATE_SET_START()		//do not delete this!!!!!!!!!!!!!!!!!!!
{
	//set delegate
	//DF_PX_LIB_SET_DELEGATE( delegate , set_function, ....params )

	//add your code here for set delegate
	/*
	// sample----------------------------------------------------------------
	DF_PX_LIB_SET_DELEGATE( custom_delegate, sample_set_delegate_1, custom_delegate);
	DF_PX_LIB_SET_DELEGATE( custom_delegate_ret, sample_set_delegate_2, custom_delegate_ret);
	// sample----------------------------------------------------------------
	*/
	
	//reg delegate with out set function
	//DF_PX_LIB_SET_DELEGATE_REG( delegate)

}
DF_PX_LIB_DELEGATE_SET_END()		//do not delete this!!!!!!!!!!!!!!!!!!!
/**************************************************************************************************************/




/**********************************add your code here when context GC******************************************/
DF_PX_LIB_ON_CTX_GC_START(ctx_)				//do not delete this!!!!!!!!!!!!!!!!!!!
{
	//add your code here when context gc

}
DF_PX_LIB_ON_CTX_GC_END()				//do not delete this!!!!!!!!!!!!!!!!!!!
/**************************************************************************************************************/




/**********************************add your code here when library free****************************************/
DF_PX_LIB_FREE_START()				//do not delete this!!!!!!!!!!!!!!!!!!!
{
	//add your code here for library free
	
}
DF_PX_LIB_FREE_END()				//do not delete this!!!!!!!!!!!!!!!!!!!
/**************************************************************************************************************/



/************************************************add solt code here********************************************/

/*
DF_PX_LIB_SLOT_START()

///////////////////////////////////////////////slot start/////////////////////
DF_PX_LIB_STOT_INIT_START(context_)
{

}
DF_PX_LIB_STOT_INIT_END()


///////////////////////////////////////////////slot tick/////////////////////
DF_PX_LIB_STOT_TICK_START()
{

}
DF_PX_LIB_STOT_TICK_END()


///////////////////////////////////////////////slot end/////////////////////
DF_PX_LIB_STOT_DONE_START(context_)
{

}
DF_PX_LIB_STOT_DONE_END()
*/

/**************************************************************************************************************/



DF_PX_LIBG_END()					//do not delete this!!!!!!!!!!!!!!!!!!!

