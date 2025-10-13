#pragma once

#define NOMINMAX

#include <vector>
#include <cstdint>
#include <limits>
#include <algorithm>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"


#include <vulkan/vulkan_raii.hpp>
#include <vulkan/vk_platform.h>

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) {
	SwapChainSupportDetails ret;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &ret.capabilities);
	uint32_t formatCnt;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCnt, nullptr);
	if (formatCnt > 0) {
		ret.formats.resize(formatCnt);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCnt, ret.formats.data());
	}
	uint32_t presentModeCnt;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCnt, nullptr);
	if (presentModeCnt > 0) {
		ret.presentModes.resize(presentModeCnt);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCnt, ret.presentModes.data());
	}
	return ret;
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(std::vector<VkSurfaceFormatKHR> availableFormats) {
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR && availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB) {
			return availableFormat;
		}
	}
	return availableFormats[0];
}

VkPresentModeKHR chooseSwapPresentMode(std::vector<VkPresentModeKHR> avaiableModes) {
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;
	for (const auto& availableMode : avaiableModes) {
		if (availableMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			bestMode = availableMode;
		}
	}
	return bestMode;
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* window) {
	//how to avoid windows min/max define
	if (capabilities.currentExtent.width != (std::numeric_limits<uint32_t>::max)()) {
		return capabilities.currentExtent;
	}
	else {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
		return actualExtent;
	}
}