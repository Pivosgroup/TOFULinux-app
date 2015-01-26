/*
 *      Copyright (C) 2012 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "system.h"
#include "AMLPowerSyscall.h"
#include "utils/AMLUtils.h"
#include "utils/log.h"

CAMLPowerSyscall::CAMLPowerSyscall()
{
#ifdef XBMC_POWERDOWN
    m_CanPowerdown = true;
#else
    m_CanPowerdown = false;
#endif
#ifdef XBMC_SUSPEND
    m_CanSuspend   = true;
#else
    m_CanSuspend   = false;
#endif
#ifdef XBMC_HIBERNATE
  m_CanHibernate = true;
#else
  m_CanHibernate = false;
#endif
#ifdef XBMC_REBOOT
  m_CanReboot    = true;
#else
  m_CanReboot    = false;
#endif

  m_OnResume  = false;
  m_OnSuspend = false;
}

bool CAMLPowerSyscall::Powerdown()
{
  return true;
}

bool CAMLPowerSyscall::Suspend()
{
  m_OnSuspend = true;
  return true;
}

bool CAMLPowerSyscall::Hibernate()
{
  return false;
}

bool CAMLPowerSyscall::Reboot()
{
  return true;
}

bool CAMLPowerSyscall::CanPowerdown()
{
  return m_CanPowerdown;
}

bool CAMLPowerSyscall::CanSuspend()
{
  return m_CanSuspend;
}

bool CAMLPowerSyscall::CanHibernate()
{
  return m_CanHibernate;
}

bool CAMLPowerSyscall::CanReboot()
{
  return m_CanReboot;
}

int CAMLPowerSyscall::BatteryLevel()
{
  return 0;
}

bool CAMLPowerSyscall::PumpPowerEvents(IPowerEventsCallback *callback)
{
  if (m_OnSuspend)
  {
    // do the CPowerManager::OnSleep() callback
    callback->OnSleep();
    m_OnResume  = true;
    m_OnSuspend = false;
    // wait for all our threads to do their thing
    usleep(1 * 1000 * 1000);
    aml_set_sysfs_str("/sys/power/state", "mem");
    usleep(100 * 1000);
  }
  else if (m_OnResume)
  {
    // do the CPowerManager::OnWake() callback
    callback->OnWake();
    m_OnResume = false;
  }

  return true;
}

bool CAMLPowerSyscall::HasAMLPowerSyscall()
{
  return aml_present();
}
