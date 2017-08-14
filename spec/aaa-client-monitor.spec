Name: aaa-client-monitor
Version: 0.0.1
Release: 1%{?dist}
Summary: AAA Client Monitor for XRootD

Group: System Environment/Daemons
License: BSD
URL: https://github.com/osschar/aaa-client-monitor
Source0: %{name}.tar.gz
BuildRoot: %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)
# BuildRequires: xrootd-server-devel xerces-c-devel pcre-devel
BuildRequires: xrootd-client-devel
BuildRequires: cmake
# Requires: /usr/bin/xrootd pcre xerces-c
Requires: /usr/bin/xrootd

%package devel
Summary: Development headers and libraries for XRootD PFC Decision UCSD plugin
Group: System Environment/Development

%description
%{summary}

%description devel
%{summary}

%prep
%setup -q -c -n %{name}-%{version}

%build

%cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .
make VERBOSE=1 %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
%{_libdir}/libXrdAaaClientMonitor-4.so.*
%{_libdir}/libXrdAaaClientMonitor-4.so

%files devel
%defattr(-,root,root,-)
%{_includedir}/AaaClientMonitor.hh

%changelog
* Mon Aug 14 2017 Matevz Tadel <mtadel@ucsd.edu> - 0.0.1-1
- First version. Build etc taken from https://github.com/osschar/xrdpfc-decision-ucsd
