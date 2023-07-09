#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/usb.h>
#include <sound/control.h>
#include <sound/core.h>
#include <sound/pcm.h>

static int volume_value = 50; // Virtual value to be controlled (katana volume emulation)

int katana_volume_get(struct snd_kcontrol *kctl, struct snd_ctl_elem_value *ucontrol)
{
	/*
		Get control callback:
		Read the current value of the control, so it can be returned to user-space.

		More:
		https://www.kernel.org/doc/html/latest/sound/kernel-api/writing-an-alsa-driver.html#info-callback
	*/
	ucontrol->value.integer.value[0] = volume_value;
	pr_info("GET volume: %d\n", volume_value);

	return 0;
}

int katana_volume_put(struct snd_kcontrol *kctl, struct snd_ctl_elem_value *ucontrol)
{
	/*
		Put control callback:
		Write a control value coming from user-space.

		More:
		https://www.kernel.org/doc/html/latest/sound/kernel-api/writing-an-alsa-driver.html#put-callback
	*/
	int changed = 0;

	if (volume_value != ucontrol->value.integer.value[0]) {
		volume_value = ucontrol->value.integer.value[0];
		pr_info("PUT volume: %d\n", volume_value);
		changed = 1;
	}

	return changed;
}

int katana_volume_info(struct snd_kcontrol *kctl, struct snd_ctl_elem_info *uinfo)
{
	/*
		Info control callback:
		Write detailed information of this control functionality into snd_ctl_elem_info
		structure.

		More:
		https://www.kernel.org/doc/html/latest/sound/kernel-api/writing-an-alsa-driver.html#info-callback
	*/
	uinfo->type		 = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count		 = 1;
	uinfo->value.integer.min = 0;
	uinfo->value.integer.max = 100;

	return 0;
}

// Control structure template
struct snd_kcontrol_new katana_vol_ctl = {
	.iface	       = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name	       = "PCM Playback Volume", // SOURCE - DIRECTION - FUNCTION
	.index	       = 0,
	.access	       = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.private_value = 0xffff,
	.get	       = katana_volume_get,
	.put	       = katana_volume_put,
	.info	       = katana_volume_info,
};