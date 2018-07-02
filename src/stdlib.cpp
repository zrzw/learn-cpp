#include <iostream>
#include <string>

std::string compose(const std::string& name, const std::string& domain)
{
  return name + "@" + domain;
}

int main()
{
  using std::cout;
  using std::endl;
  auto addr = compose("david", "zw");
  cout << addr << endl;
  return 0;
}
