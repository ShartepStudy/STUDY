#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;

class Exception {
protected:
  string message;
  int code;

public:
  Exception() {
    message = "";
  }
  Exception(string message) {
    this->message = message;
  }
  virtual void whatHappened() {
    cout << message << "\n";
  }
};

class JobImpossible : public Exception {
public:
  JobImpossible() {
    message = "";
  }
  JobImpossible(string message) : Exception(message) {}
};

class WorkerIsBusy : public JobImpossible // �������� ��� ���-�� �����
{

protected:
  string finish_working;
  string work_description;

public:
  WorkerIsBusy() {
    message = "";
  }
  WorkerIsBusy(string message) : JobImpossible(message) {}

  string getFinish_working() {
    return finish_working;
  }

  void setFinish_working(string finish_working) {
    this->finish_working = finish_working;
  }

  string getWork_description() {
    return work_description;
  }

  void setWork_description(string work_description) {
    this->work_description = work_description;
  }
};

class ForceMajor : public JobImpossible // ��������� ��
{

protected:
  double damage;
  string forcemajor_description;

public:
  ForceMajor() {
    message = "";
  }
  ForceMajor(string message) : JobImpossible(message) {}

  double getDamage() {
    return damage;
  }

  void setDamage(double damage) {
    this->damage = damage;
  }

  string getForcemajor_description() {
    return forcemajor_description;
  }

  void setForcemajor_description(string forcemajor_description) {
    this->forcemajor_description = forcemajor_description;
  }
};

class ToolsCrush : public JobImpossible // ���-�� ���������
{

protected:
  string toolcrush_description;

public:
  ToolsCrush() {
    message = "";
  }
  ToolsCrush(string message) : JobImpossible(message) {}

  string getToolcrush_description() {
    return toolcrush_description;
  }

  void setToolcrush_description(string toolcrush_description) {
    this->toolcrush_description = toolcrush_description;
  }
};

class Worker {
private:
  bool isWorking;

public:
  Worker() {
    isWorking = false;
  }

  // http://stackoverflow.com/questions/1055387/throw-keyword-in-functions-signature-c
  void Work() throw (WorkerIsBusy, ToolsCrush) {
    if (isWorking) {
      throw WorkerIsBusy("������� �����!");
    } else {
      if (verificateTools()) {
        isWorking = true;
        cout << "������� ��������...\n";
        Sleep(100);
        isWorking = false;
        cout << "������� �������� ������!\n";

        // �������� � catch (Exception exc), ���� � ��� ����� ��� ForceMajor
        throw ForceMajor("���� ��������!\n");
      } else {
        throw ToolsCrush("��, ������� ���������!\n");
      }
    }
  }

private:
  bool verificateTools() {
    int k = rand() % 2;
    return k != 0 ? true : false;
  }
};

void main() {
  setlocale(0, "");
  srand(time(0));

  Worker Andrew;

  try {
    Andrew.Work();
  } catch (ToolsCrush exc) {
    exc.whatHappened();
  } catch (WorkerIsBusy exc) {
    exc.whatHappened();
  } catch (Exception exc) {
    exc.whatHappened();
  } catch (...) {
    cout << "����� ������!";
  }
}
