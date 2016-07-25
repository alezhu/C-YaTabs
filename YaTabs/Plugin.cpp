// Plugin.cpp : Implementation of CPlugin

#include "stdafx.h"
#include "Plugin.h"


// CPlugin

STDMETHODIMP CPlugin::SetSite(IUnknown* pUnkSite)
{
	if (pUnkSite != NULL)
	{
		m_iCount = 0;
		// Cache the pointer to IWebBrowser2.
		HRESULT hr = pUnkSite->QueryInterface(IID_IWebBrowser2, (void**)&m_spWebBrowser);

		if (SUCCEEDED(hr))
		{
			// Register to sink events from DWebBrowserEvents2.
			hr = DispEventAdvise(m_spWebBrowser);
			if (SUCCEEDED(hr))
			{
				m_fAdvised = TRUE;
			}
		}

	}
	else
	{
		// Unregister event sink.
		if (m_fAdvised)
		{
			DispEventUnadvise(m_spWebBrowser);
			m_fAdvised = FALSE;
		}

		// Release cached pointers and other resources here.
		m_spWebBrowser.Release();
	}

	// Return the base class implementation
	return IObjectWithSiteImpl<CPlugin>::SetSite(pUnkSite);
}

void STDMETHODCALLTYPE CPlugin::OnDocumentComplete(IDispatch *pDisp, VARIANT *pvarURL)
{
	// Retrieve the top-level window from the site.
	//HWND hwnd;
	//HRESULT hr = m_spWebBrowser->get_HWND((LONG_PTR*)&hwnd);
	//if (SUCCEEDED(hr))
	//{
	// Output a message box when page is loaded.
	//MessageBox(hwnd, L"OnDocComplete", L"YaTabs", MB_OK);
	//}
	if (m_iCount++ != 0 ) return;
	CComBSTR url = pvarURL->bstrVal;
	if(url == _T("about:blank")) {
		CComBSTR url = _T("bar:Tabs");
		m_spWebBrowser->Navigate(url,NULL,NULL,NULL,NULL);
		DispEventUnadvise(m_spWebBrowser);
		m_fAdvised = FALSE;
	}
}

