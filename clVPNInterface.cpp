/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   clVPNInterface.cpp
 * Author: andy
 * 
 * Created on 27 July 2017, 17:19
 */

#include "clVPNInterface.h"

#include <QNetworkInterface>


clVPNInterface* clVPNInterface::s_instance = 0;

clVPNInterface* clVPNInterface::getInstance(){
    if(!s_instance) {
        s_instance = new clVPNInterface();
        // There is no instance so we created one.
        return s_instance;
    } else {
        //This is the same instance!
        return s_instance;
    }
}

bool clVPNInterface::vpnIsConnected(){

    bool result = isVPNConnected();
    if (result != m_connected) notify(result);
    return result;
}
void clVPNInterface::pollVPN(){
    if (!vpnIsConnected()) {
        m_alarmCountdown--;
        if (m_alarmCountdown <= 0){
            m_alarmCountdown = m_alarmAfter;
            emit vpnAlarm();
        }
    }
}
bool clVPNInterface::isVPNConnected(){
    QSettings settings;
    QString NetworkInterfaceName=settings.value("vpnNetworkInterfaceName").toString();
    bool result=false;
    QNetworkInterface networkInterface;
    for (auto interface : networkInterface.allInterfaces()){
        if (interface.name()==NetworkInterfaceName) {
            result=true;
            break;
        }
    }
    mu.unlock();
    return result;
}
void clVPNInterface::forceNotify(){
    m_alarmCountdown = m_alarmAfter;
    m_connected=isVPNConnected();
    notify(m_connected);
}
void clVPNInterface::notify(bool status){
    m_connected=status;
    emit vpnConnected(m_connected);
}





