/*
********************************************************************************
                                                                                
Software License Agreement                                                      
                                                                                
Copyright © 2007-2008 Microchip Technology Inc.  All rights reserved.           
                                                                                
Microchip licenses to you the right to use, modify, copy and distribute Software
only when embedded on a Microchip microcontroller or digital signal controller  
that is integrated into your product or third party product (pursuant to the    
sublicense terms in the accompanying license agreement).                        
                                                                                
You should refer to the license agreement accompanying this Software for        
additional information regarding your rights and obligations.                   
                                                                                
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,   
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF        
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.  
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER       
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR    
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES         
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR     
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF        
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES          
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.     
                                                                                
********************************************************************************
*/

// Created by the Microchip USBConfig Utility, Version 2.7.1.0, 12/10/2013, 11:02:53

#ifndef _usb_config_h_
#define _usb_config_h_

#if defined(__PIC24F__)
    #include <p24fxxxx.h>
#elif defined(__18CXX)
    #include <p18cxxx.h>
#elif defined(__PIC32MX__)
    #include <p32xxxx.h>
    #include "plib.h"
#else
    #error No processor header file.
#endif

#define _USB_CONFIG_VERSION_MAJOR 2
#define _USB_CONFIG_VERSION_MINOR 7
#define _USB_CONFIG_VERSION_DOT   1
#define _USB_CONFIG_VERSION_BUILD 0

// Supported USB Configurations

#define USB_SUPPORT_DEVICE

// Hardware Configuration

#define USB_PING_PONG_MODE  USB_PING_PONG__NO_PING_PONG

// Peripheral Configuration

#define MY_VID            0x04D8
#define MY_PID            0x0000
#define USB_SPEED_OPTION       USB_LOW_SPEED 
#define USB_POLLING
#define USB_PULLUP_OPTION      USB_PULLUP_ENABLE
#define USB_TRANSCEIVER_OPTION USB_INTERNAL_TRANSCEIVER
#define USB_EP0_BUFF_SIZE     8
#define USB_MAX_NUM_INT       (0+1)
#define USB_MAX_EP_NUMBER 6
#define USB_NUM_STRING_DESCRIPTORS 3

//#define USB_DISABLE_SOF_HANDLER                 
//#define USB_DISABLE_ERROR_HANDLER               
//#define USB_DISABLE_SET_DESCRIPTOR_HANDLER      

// HID Function Configuration

#define USB_USE_HID
#define HID_INTF_ID             0x00
#define HID_EP 					1
#define HID_INT_IN_EP_SIZE      3
#define HID_INT_OUT_EP_SIZE     3
#define HID_NUM_OF_DSC          1
#define HID_RPT01_SIZE          50

#endif

