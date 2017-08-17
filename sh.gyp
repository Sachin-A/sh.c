{
	'targets': [
		{
			'target_name': 'shell',
			'type': 'executable',
			'include_dirs': [
				'include',
			],
			'sources': [
				'src/sh.c',
				'src/utility.c',
			],
			'cflags': [
				'-std=gnu99',
			],
		},
	],
}
