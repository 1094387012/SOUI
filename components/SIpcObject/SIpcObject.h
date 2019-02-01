#pragma once
#include <windows.h>
#include <interface/SIpcObj-i.h>
#include <unknown/obj-ref-impl.hpp>
#include <map>
namespace SOUI
{
	class SIpcObject
	{
	public:
		SIpcObject();
		~SIpcObject();
	};

	class SIpcServer : public TObjRefImpl<IIpcServer>
	{
	public:
		SIpcServer() :m_pCallback(NULL) {}

	public:
		// ͨ�� TObjRefImpl �̳�
		virtual void SetCallback(IIpcSvrCallback * pCallback) override;
		virtual void CheckConectivity() override;

	private:
		IIpcSvrCallback * m_pCallback;
		std::map<ULONG_PTR, IIpcConnection *> m_mapClients;
	};

	class SIpcFactory : public TObjRefImpl<IIpcFactory>
	{
	public:
		// ͨ�� TObjRefImpl �̳�
		virtual HRESULT CreateIpcServer(IIpcServer ** ppServer) override;
		virtual HRESULT CreateIpcConnection(IIpcConnection ** ppConn) override;
	};
	namespace IPC
	{
		SOUI_COM_C BOOL SOUI_COM_API SCreateInstance(IObjRef **ppIpcFactory);
	}
}

