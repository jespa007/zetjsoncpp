#pragma once

namespace zetjsoncpp {

enum{

	CFunctor_UNKNOW=0,
	CFunctor_VOID_VOID=1,
	CFunctor_BOOLEAN_FUNCTION

};

#define NEW_VOID_MEMBER_FUNCTION(v,c,f) 		(new CPointerFunctionParam0Caller<c>(v,&c::f))
#define THIS_FUNCTION_POINTER(o,f)				(new CPointerFunctionParam0Caller<o>(this,&o::f))


template
<class TSignature, int _instance> class  CFunctor{

	int instance;

protected:
	typedef TSignature instance_signature;

      public:
			CFunctor() 	{

				instance  =  _instance;
			}

            //  two  possible  functions  to  call  member  function.  virtual  cause  derived
            //  classes  will  use  a  pointer  to  an  object  and  a  pointer  to  a  member  function
            //  to  make  the  function  call
            virtual  instance_signature  operator()(void)=0;    //  call  using  operator
            virtual  instance_signature  Call()=0;                //  call  using  function

            virtual ~CFunctor(){}
};
//--------------------------------------------------------------------------------------------
typedef CFunctor<void,CFunctor_VOID_VOID> CVoidFunctor;
typedef CFunctor<bool,CFunctor_BOOLEAN_FUNCTION> CBooleanFunctor;

#define VOID_FUNCTOR(T_CLASS, FUNCTION) CGenericVoidMemberFunction<T_CLASS>(this,&T_CLASS::FUNCTION_OBJECT)




template <class TClass>
class  CGenericVoidMemberFunction  :  public  CFunctor<void, CFunctor_VOID_VOID>
      {
      private:
            instance_signature  (TClass::*fpt)(void);      //  pointer  to  member  function
            TClass*  pt2Object;                                    //  pointer  to  object

      public:

            CGenericVoidMemberFunction() {  }

            //  constructor  -  takes  pointer  to  an  object  and  pointer  to  a  member  and  stores
            //  them  in  two  private  variables
            CGenericVoidMemberFunction(TClass*  _pt2Object,
                                                instance_signature (TClass::*_fpt)(void)
                                                )
              {

                      pt2Object  =  _pt2Object;
                      fpt=_fpt;

            }

            void SetFunction(TClass*  _pt2Object,
                                                instance_signature(TClass::*_fpt)(void)
                                                )
              {

                      pt2Object  =  _pt2Object;
                      fpt=_fpt;

            }

            //  override  operator  "()"
            virtual  instance_signature  operator()(void)
              {   (*pt2Object.*fpt)();};                            //  execute  member  function

            //  override  function  "Call"
            virtual  instance_signature  Call()
                {   (*pt2Object.*fpt)();};                          //  execute  member  function
      };


//-------------------------------------------------------------------------------------------------


class CPointerFunctionParam0{
	public:
		virtual void call()=0;
		virtual ~CPointerFunctionParam0(){}
};

template <class _T>
class CPointerFunctionParam0Caller: public CPointerFunctionParam0{

	void (_T::* m_func) ( );
	_T *ptr;
public:
	CPointerFunctionParam0Caller(_T *obj,void (_T::* _func) ())
	{
		m_func =_func;
		ptr = obj;
	}

	virtual void call(){
		//cout << "hola xaval " << i1;

		((*ptr).*m_func) ();

	}
};

template <typename _TPARAM>
class CPointerFunctionParam1{
	public:
		virtual void call(_TPARAM parameter)=0;

		virtual ~CPointerFunctionParam1(){}
};

template <class _T,typename _TPARAM>
class CPointerFunctionParam1Caller: public CPointerFunctionParam1<_TPARAM>{

	void (_T::* m_func) (_TPARAM );
	_T *ptr;
public:
	CPointerFunctionParam1Caller(_T *obj,void (_T::* _func) ( _TPARAM ))
	{
		m_func =_func;
		ptr = obj;
	}

	virtual void call( _TPARAM parameter){
		//cout << "hola xaval " << i1;

		((*ptr).*m_func) (parameter);

	}
};

};
