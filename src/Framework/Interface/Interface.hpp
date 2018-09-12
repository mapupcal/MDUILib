
#ifndef MDUILIB_FRAMEWORK_INTERFACE_INTERFACE_H
#define MDUILIB_FRAMEWORK_INTERFACE_INTERFACE_H

#define m_interface struct
#define m_implements public
#define m_extends public 

#define m_T(str) AString(#str)

#define m_interface_name(InterfaceType) m_T(CRTII_NAME_##InterfaceType)

#endif //MDUILIB_FRAMEWORK_INTERFACE_INTERFACE_H