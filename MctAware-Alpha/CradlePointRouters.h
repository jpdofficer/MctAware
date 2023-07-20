#ifndef CRADLEPOINTROUTERS_H
#define CRADLEPOINTROUTERS_H
/**
 * @brief The CradlePoint Router class
 * @author John Yeager
 * @copyright 07/07/2023
 * Purpose: The purpose of this class is to store the data provided by the routers.csv that is provided by netcloud
 *
 */
#include<string>
#include<QVector>

class CradlePointRouter
{
    public:
    CradlePointRouter();
        ~CradlePointRouter();





    private:
        unsigned int id; // the id of the router
        std::string state; // the state of the router(Online,Offine, Initalized)
        unsigned int last_fw_activity; // the last forwarding activity of the router
        bool is_individually_configured; // where the router is configured individually or not
        std::string name; //the name of the router
        std::string desc; // a description of the router
        std::string asset_id; //the assigned asset id( it could be a series of letters and numbers)
        std::string mac; //the mac address of the router
        std::string ip_address; //the ip address of the router
        std::string full_product_name; // the full product name of the router
        std::string group__name; //the group name of the router
        std::string actual_firmware__version; //the actual firmware Version used by this router
        std::string actual_firmware__build_timestamp; // the date and time that the firmware was changed


};

#endif // CRADLEPOINTROUTERS_H
