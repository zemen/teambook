#include "../../include/wtf/terve_generator.h"

using tamias::wtf::terve::Entity;
using tamias::wtf::terve::Generator;

Generator::Generator() : mStrings(), mLines(), mGroups(), mI18n(), mVariables()
{
}

Generator::Generator( const Generator &generator ) : mStrings(generator.mStrings), mLines(generator.mLines),
                                                     mGroups(generator.mGroups), mI18n(generator.mI18n),
                                                     mVariables(generator.mVariables)
{
}

Generator& Generator::operator = ( const Generator &generator )
{
  mStrings = generator.mStrings;
  mLines = generator.mLines;
  mGroups = generator.mGroups;
  mI18n = generator.mI18n;
  mVariables = generator.mVariables;
  return *this;
}

Generator::~Generator()
{
}

Generator& Generator::setVariable( const tamias::String &name, const Entity &value )
{
  mVariables[name] = value;
  return *this;
}

Entity Generator::addText( const tamias::String &text )
{
  return Entity(Entity::ENTITY_TEXT, createString(text));
}

Entity Generator::addI18n( const tamias::String &text )
{
  mI18n[text] = text; // By default, this map is simple. TODO: document this.
  return Entity(Entity::ENTITY_I18N, createString(text));
}

Entity Generator::addLine( const tamias::Vector <Entity> &line, tamias::sizetype indent )
{
  tamias::sizetype index = createLine();
  mLines[index] = tamias::makePair(line, indent);
  return Entity(Entity::ENTITY_LINE, index);
}

Entity Generator::addGroup( const tamias::Vector <Entity> &group )
{
  tamias::sizetype index = createGroup();
  mGroups[index] = group;
  return Entity(Entity::ENTITY_GROUP, index);
}

Entity Generator::addTemplate( const tamias::ByteArray &fileName )
{
  using tamias::sizetype;
  using tamias::String;
  using tamias::makePair;
  tamias::Scanner scanner(tamias::File::openRead(fileName));
  tamias::ByteArray scanData = ""; // TODO: smth like scanner.readAll()
  while (scanner.eof() == false)
    scanData += scanner.nextByte();
  tamias::String data = scanData;
  scanner.close();
  sizetype result = createGroup();
  sizetype line = createLine();
  String temp = "";
  for (sizetype i = 0; i < data.length(); i++)
  {
    if (data[i] == '\n')
    {
      if (temp != "")
        mLines[line].first.pushBack(addText(temp)), temp = "";
      mGroups[result].pushBack(Entity(Entity::ENTITY_LINE, line));
      line = createLine();
      continue;
    }
    if (data[i] != '{')
    {
      temp += data[i];
      continue;
    }
    if (++i >= data.length())
      continue;
    if (data[i] == '{')
    {
      temp += data[i];
      continue;
    }
    tamias::Vector <String> rules;
    while (data[i] != '}')
    {
      String str = "";
      while (data[i] != ':' && data[i] != '}')
      {
        if (data[i] == '\\' && ++i >= data.length())
          break;
        str += data[i];
        if (++i >= data.length())
          break;
      }
      rules.pushBack(str);
      if (i >= data.length() || data[i] == '}')
        break;
      i++;
    }
    if (rules.size() < 1)
      continue;
    String module = rules[0];
    if (module == "i18n" && rules.size() >= 2)
    {
      if (temp != "")
        mLines[line].first.pushBack(addText(temp)), temp = "";
      mLines[line].first.pushBack(addI18n(rules[1]));
    }
    else if (module == "template" && rules.size() >= 2)
    {
      if ((rules.size() == 2 || !tamias::wtf::utilities::testString(temp, ' ')) && temp != "")
        mLines[line].first.pushBack(addText(temp)), temp = "";
      if (mVariables.count(rules[1]) != 0)
        mLines[line].first.pushBack(mVariables[rules[1]]);
      if (rules.size() >= 3)
      {
        mLines[line].second = tamias::wtf::utilities::stringToInt(rules[2]);
        if (mLines[line].first.size() != 0)
          mGroups[result].pushBack(Entity(Entity::ENTITY_LINE, line));
        line = createLine();
        if (i + 1 < data.size() && data[i + 1] == '\n')
          i++;
        temp = "";
      }
    }
    else
    {
      // TODO: say about strange template
    }
  }
  if (temp != "")
    mLines[line].first.pushBack(addText(temp)), temp = "";
  if (mLines[line].first.size() > 0)
    mGroups[result].pushBack(Entity(Entity::ENTITY_LINE, line));
  return Entity(Entity::ENTITY_GROUP, result);
}

tamias::Map <tamias::RBSTree, tamias::String, tamias::String>& Generator::i18n()
{
  return mI18n;
}

tamias::String Generator::assemble( const Entity &root )
{
  tamias::String result = "";
  dfs(root, result, 0);
  return result;
}

void Generator::clear()
{
  mStrings.clear();
  mLines.clear();
  mGroups.clear();
  mI18n.clear();
//  mI18n = tamias::Map <tamias::RBSTree, tamias::String, tamias::String> ();
  mVariables.clear();
//  mVariables = tamias::Map <tamias::RBSTree, tamias::String, Entity> ();
}

tamias::String Generator::escape( const tamias::String &s )
{
  String r;
  for (tamias::sizetype i = 0; i < s.length(); i++)
    switch (s[i])
    {
      case '<': r += "&lt;"; break;
      case '>': r += "&gt;"; break;
      case '\"': r += "&quot;"; break;
      case '&': r += "&amp;"; break;
      default: r += s[i];
    }
  return r;
}

tamias::sizetype Generator::createString( const tamias::String &string )
{
  tamias::sizetype index = mStrings.size();
  mStrings.pushBack(string);
  return index;
}

tamias::sizetype Generator::createLine()
{
  tamias::sizetype index = mLines.size();
  mLines.pushBack(tamias::makePair(tamias::Vector<Entity>(), 0));
  return index;
}

tamias::sizetype Generator::createGroup()
{
  tamias::sizetype index = mGroups.size();
  mGroups.pushBack(tamias::Vector <Entity> ());
  return index;
}

void Generator::dfs( const Entity& entity, tamias::String &result, tamias::sizetype indent )
{
  using tamias::sizetype;
  switch (entity.type())
  {
    case Entity::ENTITY_EMPTY:
      break;
    case Entity::ENTITY_TEXT:
      result += mStrings[entity.value()];
      break;
    case Entity::ENTITY_I18N:
      result += mI18n[mStrings[entity.value()]];
      break;
    case Entity::ENTITY_LINE:
    {
      if (mLines[entity.value()].first.size() == 0)
        break;
      sizetype currentIndent = indent + mLines[entity.value()].second;
      for (sizetype i = 0; i < currentIndent; i++)
        result += ' ';
      for (sizetype i = 0; i < mLines[entity.value()].first.size(); i++)
        dfs(mLines[entity.value()].first[i], result, currentIndent);
      result += '\n';
      break;
    }
    case Entity::ENTITY_GROUP:
    {
      for (sizetype i = 0; i < mGroups[entity.value()].size(); i++)
        dfs(mGroups[entity.value()][i], result, indent);
      break;
    }
  }
}

