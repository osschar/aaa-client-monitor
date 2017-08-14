#ifndef AAA_CLIENT_MONITOR_HH
#define AAA_CLIENT_MONITOR_HH

#include "XrdCl/XrdClMonitor.hh"

#include <map>


class AaaClMon : public XrdCl::Monitor
{
protected:
  const char* code2name(XrdCl::Monitor::EventCode evCode);

  std::map<const XrdCl::URL*, std::string> m_urlptr_to_something;
  
public:
  AaaClMon(const char *exec, const char *parms);
  ~AaaClMon();

  void Event(XrdCl::Monitor::EventCode evCode, void *evData) override;
};

#endif
