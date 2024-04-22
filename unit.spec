#+======================================================================
# $HeadURL: $
# $Id: $
#
# Project       : Supervision and Automation - Dependency injection
#
# Description   : The definition and implementation for dependency injection templates in SUP.
#
# Author(s)     : Walter Van Herck (IO)
#
# Copyright (c) : 2010-2024 ITER Organization,
#                 CS 90 046
#                 13067 St. Paul-lez-Durance Cedex
#                 France
#
# This file is part of ITER CODAC software.
# For the terms and conditions of redistribution or use of this software
# refer to the file ITER-LICENSE.TXT located in the top level directory
# of the distribution package.
#
#-======================================================================

%define        _build_id_links none
%define        __brp_ldconfig %{nil}
%define        __brp_strip %{nil}

Name:         %{project_artifactId}
Version:      %{project_version}
Release:      %{?rpm_release_num:%{rpm_release_num}%{?dist}}%{!?rpm_release_num:0%{?dist}}
Summary:      %{project_name}

Group:        Development/CODAC
Distribution: CODAC Operation Applications
URL:          %{?rpm_vcs_url:%{rpm_vcs_url}}%{!?rpm_vcs_url:undefined}
Vendor:       ITER Organization
Packager:     ITER Organization
License:      ITER License

AutoReq:      no

%provides_self

%description
%{project_description}.

%package -n %subpackage devel
Summary:      %{project_description} - Development files
Group:        Development/CODAC
AutoReq:      no
Requires:     %{project_artifactId}
%provides_self %subpackage devel

%description -n %subpackage devel
%{project_description} - Development files.

%package -n %subpackage docs
Summary:      %{project_description} - Documentation
Group:        Development/CODAC
AutoReq:      no
Requires:     %{project_artifactId}
%provides_self %subpackage docs

%description -n %subpackage docs
%{project_description} - Documentation.

%prep

%build

%install
rm -rf %{buildroot}
install -d %{buildroot}/opt/codac/bin
cp -r %{project_target}/bin/* %{buildroot}/opt/codac/bin
install -d %{buildroot}/opt/codac/lib
cp -r %{project_target}/lib/* %{buildroot}/opt/codac/lib
install -d %{buildroot}/opt/codac/doc/%{project_artifactId}
cp -r %{project_target}/doc/%{project_artifactId} %{buildroot}/opt/codac/doc/%{project_artifactId}
install -d %{buildroot}/opt/codac/include
cp -r %{project_target}/include/* %{buildroot}/opt/codac/include

%clean

%files
%dir /opt/codac
%dir /opt/codac/bin
%dir /opt/codac/lib
/opt/codac/bin/*
/opt/codac/lib/*.so.*

%files -n %subpackage devel
/opt/codac/include
/opt/codac/lib/*.so
/opt/codac/lib/cmake

%files -n %subpackage docs
/opt/codac/doc/%{project_artifactId}

%changelog
* Mon Apr 22 2024 Walter Van Herck <walter.vanherck@iter.org>
- See ChangeLog.