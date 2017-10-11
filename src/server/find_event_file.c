#include "find_event_file.h"

#define INPUT_DIR "/dev/input/"

static int is_char_device(const struct dirent *file){
  struct stat file_stat;
  char file_name[256];
  int err;

  snprintf(file_name, sizeof(file_name), "%s%s", INPUT_DIR, file->d_name);

  err = stat(file_name, &file_stat);
  if(err){
    printf("ERROR IS CHAR\n");
    return 0;
  }

  return S_ISCHR(file_stat.st_mode);
}

char *get_keyboard_event_file(void){
  char *keyboard_file = NULL;
  int num, i;
  struct dirent **event_files;
  char file_name[256];

  num = scandir(INPUT_DIR, &event_files, &is_char_device, &alphasort);
  if(num < 0){
    return NULL;
  }else{
    for(i=0; i<num; i++){
      
      int32_t event_bitmap = 0;
      int fd;
      int32_t kbd_bitmap = KEY_A | KEY_B | KEY_C | KEY_Z;

      snprintf(file_name, sizeof(file_name), "%s%s", INPUT_DIR, event_files[i]->d_name);
      fd = open(file_name, O_RDONLY);

      if(fd == -1){
	perror("OPEN_ERROR");
	continue;
      }

      ioctl(fd, EVIOCGBIT(0, sizeof(event_bitmap)), &event_bitmap);

      if((EV_KEY & event_bitmap) == EV_KEY){
	//le device réagit comme un keyboard
	
	ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(event_bitmap)), &event_bitmap);
	if((kbd_bitmap & event_bitmap) == kbd_bitmap){
	  //le device supporte les touches A, B, C, Z donc ==>keyboard

	  keyboard_file = strdup(file_name);
	  close(fd);
	  break;
	}

      }
      close(fd);
    }
  }

  //clean
  for(i=0; i<num; i++){
    free(event_files[i]);
  }

  free(event_files);

  return keyboard_file;
}


