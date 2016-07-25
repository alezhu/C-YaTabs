// dllmain.h : Declaration of module class.

class CYaTabsModule : public ATL::CAtlDllModuleT< CYaTabsModule >
{
public :
	DECLARE_LIBID(LIBID_YaTabsLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_YATABS, "{A93F0EA1-B798-4396-85FF-1AD1E880C948}")
};

extern class CYaTabsModule _AtlModule;
