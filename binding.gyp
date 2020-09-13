{
	"variables": {
			"dll_files": [
				"<(module_root_dir)/sdk/bin/depthengine_2_0.dll",
				"<(module_root_dir)/sdk/bin/k4a.dll",
				"<(module_root_dir)/sdk/bin/k4arecord.dll",
			],
	},

	"targets": [
		{
			"target_name": "AzureKinectDevice",
			"cflags!": [
				"-fno-exceptions"
			],
        	"cflags_cc!": [
			 	"-fno-exceptions"
			 ],
			"sources": [
				"./src/binding.cpp",
				"./src/AzureKinectDevice.cpp",
				"./src/AzureKinectDeviceWrapper.cpp"
			],
			"include_dirs": [
				"<(module_root_dir)/sdk/include",
				"<!@(node -p \"require('node-addon-api').include\")",
			],
			"libraries": [
				"<(module_root_dir)/sdk/lib/k4a.lib",
				"<(module_root_dir)/sdk/lib/k4arecord.lib",
			],
			'dependencies': [
            	"<!(node -p \"require('node-addon-api').gyp\")"
        	],
			 "copies": [
	            {
	              "destination": "<(module_root_dir)/build/Release",
	              "files": [
				  	"<(module_root_dir)/sdk/bin/depthengine_2_0.dll",
					"<(module_root_dir)/sdk/bin/k4a.dll",
					"<(module_root_dir)/sdk/bin/k4arecord.dll",
				   ]
	            }
          	],
		  	'defines': [
				'NAPI_DISABLE_CPP_EXCEPTIONS'
			]
		}
	]
}
