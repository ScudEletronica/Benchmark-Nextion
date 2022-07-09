#include "Nextion/doxygen.h"
#include "Nextion/NexPage.h"
#include "Nextion/NexText.h"
#include "Nextion/Nextion.h"

NexText alertName = NexText(1, 4, "t1");
NexText alertValue = NexText(1, 5, "t2");

NexPage page0 = NexPage(0, 0, "page0");
NexPage page1 = NexPage(1, 0, "page1");

bool isAlertPage = false;
bool alertPage = false;

class NexValue {
  private:
    bool overflow = false;
    float min;
    float max;
    String name;
    bool display;

    NexText *t;
  public:
    static int amount;

    NexValue(String name, float min, float max, bool display = false, uint8_t pid = 0, uint8_t cid = 0, const char *variable = "") {
      this->min = min;
      this->max = max;
      this->name = name;
      this->display = display;
      alertPage = false;
      amount++;
      if (display) {
        t = new NexText(pid, cid, variable);
      }
    }

    void evaluate(float value) {
      if (min > value || value > max) {
        overflow = true;
        isAlertPage = true;
        alert(value);
      } else {
        if (overflow) {
          overflow = false;
          isAlertPage = false;
        } 
        if (display && !isAlertPage) {
          show(value);
        }
      }
    }

    void alert(float value) {
      char txt[10];
      memset(txt, 0, sizeof(txt));
      itoa(value, txt, 10);
      
      if (!alertPage) {
        page1.show();
        alertPage = true;
      }
      alertName.setText(name.c_str());
      alertValue.setText(txt);
    }

    void show(float value) {
      char txt[10];
      memset(txt, 0, sizeof(txt));
      itoa(value, txt, 10);
      
      if (alertPage) {
        page0.show();
        alertPage = false;
      }
      t->setText(txt);
    }
};

int NexValue::amount = 0;