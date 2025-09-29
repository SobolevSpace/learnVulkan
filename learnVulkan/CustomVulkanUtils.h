#pragma once
#include <string>
#include <vulkan/vulkan_raii.hpp>
#include <vulkan/vk_platform.h>


namespace CustomVulkanUtils {
    std::string SeverityToString(VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
        switch (severity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return "VERBOSE";
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return "INFO";
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return "WARNING";
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return "ERROR";
        default: return "UNKNOWN";
        }
    }

    std::string MessageTypeToString(VkDebugUtilsMessageTypeFlagsEXT messageType)
    {
        std::string result;
        if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT)
            result += "GENERAL|";
        if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT)
            result += "VALIDATION|";
        if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
            result += "PERFORMANCE|";

        if (!result.empty()) {
            // È¥µôÄ©Î²µÄ '|'
            result.pop_back();
        }
        else {
            result = "UNKNOWN";
        }
        return result;
    }

    void PrintDevice(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    }

}