#
# spec file for package myapp (Version 1.0)
#

Vendor:           Wrox Press
Distribution:     Any
Name:	          myapp
Version:	  1.0
Release:          1
Packager:         neil@provider.com
License:	  Copyright 2007 Wiley Publishing, Inc.
Group:            Applications/Media

Provides:         goodness
Requires:         mysql >= 3.23

Buildroot:        %{_tmppath}/%{name}-%{version}-root
source:		  %{name}-%{version}.tar.gz

Summary:	  Trivial Application

%description
MyAPP Trivial Application

A trivial application used to demonstrate development tools.
This version pretends it requires MySQL at or above 3.23.

Authors: Neil Matthew and Richard Stones

%prep
%setup -q

%build
make

%install
mkdir -p $RPM_BUILD_ROOT%{_bindir}
mkdir -p $RPM_BUILD_ROOT%{_mandir}
install -m755 myapp $RPM_BUILD_ROOT%{_bindir}/myapp
install -m755 myapp.1 $RPM_BUILD_ROOT%{_mandir}/myapp.1

%clean
rm -rf $RPM_BUILD_ROOT

%post
mail root -s "myapp installed - please register" </dev/null

%files
%{_bindir}/myapp
%{_mandir}/myapp.1.gz
