#pragma once
#include <sound/control.h>

int katana_volume_get(struct snd_kcontrol *kctl, struct snd_ctl_elem_value *ucontrol);
int katana_volume_put(struct snd_kcontrol *kctl, struct snd_ctl_elem_value *ucontrol);
int katana_volume_info(struct snd_kcontrol *kctl, struct snd_ctl_elem_info *uinfo);

extern struct snd_kcontrol_new katana_vol_ctl;
