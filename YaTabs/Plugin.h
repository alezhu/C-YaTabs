// Plugin.h : Declaration of the CPlugin

#pragma once
#include "resource.h"       // main symbols
#include <shlguid.h> // IID_IWebBrowser2, DIID_DWebBrowserEvents2, etc.
#include <exdispid.h> // DISPID_DOCUMENTCOMPLETE, etc.


#include "YaTabs_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CPlugin

class ATL_NO_VTABLE CPlugin :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPlugin, &CLSID_Plugin>,
	public IObjectWithSiteImpl<CPlugin>,
	public IDispatchImpl<IPlugin, &IID_IPlugin, &LIBID_YaTabsLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispEventImpl<1, CPlugin, &DIID_DWebBrowserEvents2, &LIBID_SHDocVw, 1, 1>
{
public:
	CPlugin()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PLUGIN)


BEGIN_COM_MAP(CPlugin)
	COM_INTERFACE_ENTRY(IPlugin)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()

BEGIN_SINK_MAP(CPlugin)
    SINK_ENTRY_EX(1, DIID_DWebBrowserEvents2, DISPID_DOCUMENTCOMPLETE, OnDocumentComplete)
END_SINK_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(SetSite)(IUnknown *pUnkSite);
    // DWebBrowserEvents2
 void STDMETHODCALLTYPE OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL);

private:
    CComPtr<IWebBrowser2>  m_spWebBrowser;
	BOOL m_fAdvised;
	int m_iCount;

};

OBJECT_ENTRY_AUTO(__uuidof(Plugin), CPlugin)
