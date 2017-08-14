#include "AaaClientMonitor.hh"

#include <cstring>

//------------------------------------------------------------------------------

#include "XrdVersion.hh"

XrdVERSIONINFO(XrdClGetMonitor, "aaa-cl-monitor");

extern "C"
{
  XrdCl::Monitor* XrdClGetMonitor(const char *exec, const char *parms)
  {
    return new AaaClMon(exec, parms);
  }
}

//------------------------------------------------------------------------------

const char* AaaClMon::code2name(XrdCl::Monitor::EventCode evCode)
{
  switch (evCode)
  {
    // perl -ne 'm/^\s*(\w+)/; print "  case XrdCl::Monitor::$1 : return \"$1\";\n";'
    case XrdCl::Monitor::EvCopyBeg : return "EvCopyBeg";
    case XrdCl::Monitor::EvCopyEnd : return "EvCopyEnd";
    case XrdCl::Monitor::EvCheckSum : return "EvCheckSum";
    case XrdCl::Monitor::EvOpen : return "EvOpen";
    case XrdCl::Monitor::EvClose : return "EvClose";
    case XrdCl::Monitor::EvErrIO : return "EvErrIO";
    case XrdCl::Monitor::EvConnect : return "EvConnect";
    case XrdCl::Monitor::EvDisconnect : return "EvDisconnect";
    default: return "<unknown>";
  }
}

AaaClMon::AaaClMon(const char *exec, const char *parms)
{
  printf("AaaClMon::AaaClMon exec='%s', parms='%s'\n",
         exec ? exec : "<null>", parms ? parms : "<null>");
}

AaaClMon::~AaaClMon()
{
  printf("AaaClMon::~AaaClMon\n");
}

void AaaClMon::Event(XrdCl::Monitor::EventCode evCode, void *evData)
{
  printf("AaaClMon::Event %s\n", code2name(evCode));

  switch (evCode)
  {
    case XrdCl::Monitor::EvCopyBeg:
    {
      break;
    }
    case XrdCl::Monitor::EvCopyEnd:
    {
      break;
    }
    case XrdCl::Monitor::EvCheckSum:
    {
      break;
    }
    case XrdCl::Monitor::EvOpen:
    {
      auto& i  = * (XrdCl::Monitor::OpenInfo *) evData;

      printf("  '%s' (%p) at '%s'\n",
             i.file->GetURL().c_str(), i.file, i.dataServer.c_str());

      // Here should, maybe, instantiate some bigger access stats structure.
      // Esp. if we add events for individual reads.
      // Must check URL* is actually unique and persistent.
      // It does seem persistent ... not yet sure about unique, would need
      // to test it with cmssw multi-source reading.
      m_urlptr_to_something[i.file] = i.dataServer;

      break;
    }
    case XrdCl::Monitor::EvClose:
    {
      auto& i  = * (XrdCl::Monitor::CloseInfo *) evData;

      printf("  '%s' (%p) have entry in urlptr map=%d\n",
             i.file->GetURL().c_str(), i.file,
             m_urlptr_to_something.find(i.file) != m_urlptr_to_something.end());
      break;
    }
    case XrdCl::Monitor::EvErrIO:
    {
      break;
    }
    case XrdCl::Monitor::EvConnect:
    {
      break;
    }
    case XrdCl::Monitor::EvDisconnect:
    {
      auto& i  = * (XrdCl::Monitor::DisconnectInfo *) evData;

      printf("  '%s' rcv:%lu snt:%lu time:%ld status:'%s'",
             i.server.c_str(), i.rBytes, i.sBytes, i.cTime, i.status.ToString().c_str());
      break;
    }
  }
    
}
