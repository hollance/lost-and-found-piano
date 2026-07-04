#include "Settings.h"

Settings::Settings()
{
    juce::PropertiesFile::Options propertyOptions {};
    propertyOptions.applicationName = "Piano";
    propertyOptions.filenameSuffix = ".settings";
    propertyOptions.folderName = "Lost N Found";
    propertyOptions.osxLibrarySubFolder = "Application Support";
    propertyOptions.commonToAllUsers = false;
    applicationProperties.setStorageParameters(propertyOptions);

    settings = applicationProperties.getUserSettings();
}

Settings::~Settings()
{
    applicationProperties.closeFiles();
}

void Settings::reload()
{
    settings->reload();
}

void Settings::setWindowWidth(int width)
{
    settings->setValue("windowWidth", width);
    applicationProperties.saveIfNeeded();
}

int Settings::getWindowWidth() const
{
    return settings->getIntValue("windowWidth", defaultWidth);
}
