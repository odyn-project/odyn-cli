Odyn CLI
---------

Commands

    alias       Create, list or delete a device alias
    config      Configure local or remote settings
    device      Create, list, describe or delete a device
    push        Push cloud variable data to the remote server
    org         Create, describe, modify or delete an an organization
    fetch       Fetch cloud variable data from the remote server
    subscribe   Listen to the remote server for changes to a cloud variable
    user        Create, describe, modify or delete an a user


All devices belong to either a user or an organization.



    push http://odyn.io/MyOrg/MyDevice/gps/latitude 53.43232

    odyn config remote.db.backend "cassandra"


Quick Start Guide
---------

Installation:

    apt-get install odyn

Start the server:

    sudo service odyn start

Create a user (named "Leela"):

    odyn user --create Leela
    
    (You will be prompted to set a password)


Create a device:

    odyn device --create Leela.HealthMonitor

Push data to the server:

    odyn push Leela.HealthMonitor.heartrate 140.3


Monitor data from the server (ctrl-C to cancel):

    odyn subscribe Leela.HealthMonitor

View the device's admin webpage:

    In your browser, go to: http://localhost:7280/Leela/HealthMonitor
