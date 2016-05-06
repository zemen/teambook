#pragma once

#include "../basic/byte_array.h"
#include "../basic/string.h"
#include "../basic/types.h"
#include "../data/pair.h"
#include "../main/map.h"
#include "../main/tree_rbst.h"
#include "../main/vector.h"
#include "../io/file.h"
#include "../io/scanner.h"
#include "../wtf/utilities.h"
#include "../wtf/terve_entity.h"

/*
 * У меня самого не получилось через 2 дня вспомнить, что на что а как должно ссылаться.
 * Видимо, это означает, что надо написать какое-то описание. —burunduk3
 *
 * Есть следующие сущности:
 *   1. Строчка (ENTITY_STRING). Характеризуется индексом в массиве templateStrings, означает тупо текст.
 *   2. Непереведённая строчка (ENTITY_I18N). Характеризуется индексом в templateStrings и значением
 *     в отображении templateI18n. Означает строчку, к которой ещё нужно применить (это происходит в
 *     функции assemble) это отображение.
 *   3. Встроенный кусок (ENTITY_PART). Характеризуется индексом в templateParts, означает набор
 *     сущностей.
 *   4. Выключный кусок (ENTITY_MULTIPART). Характеризется индексом в templateMutliParts, означает
 *     набор полных строк (line) и сдвигов — на сколько требуется сдвинуть все внутренние строки, если
 *     это ссылка на другой выключный кусок. Сдвиги складываются.
 * Вспомогательные элементы:
 *   1. Переменные. Отображение строчек в сущности.
 *   2. Полная строка. Набор сущностей.
 * TODO:
 *   1. Выделить элемент «ссылка на шаблон». Зачем?
 *   2. Сделать line отдельной сущностью.
 *   3. Переписать это описание ^_^
 * Внезапно! Объекты типа Entity вообще-то жёстко привязаны к шаблону. Так-то.
 */

namespace tamias
{
  namespace wtf
  {
    namespace terve
    {
      class Generator
      {
        public:
          Generator();
          Generator( const Generator &generator );
          Generator& operator = ( const Generator &generator );
          ~Generator();
    
          Generator& setVariable( const String &name, const Entity &entity );
          // методы add{Test,I18n,Line,Group,Template} возвращают ссылку на построенную сущность.
          Entity addText( const String &text );
          Entity addI18n( const String &text );
          Entity addLine( const Vector <Entity> &line, sizetype indent = 0 );
          Entity addGroup( const Vector <Entity> &group);
          Entity addTemplate( const ByteArray &fileName );
          Map <RBSTree, String, String>& i18n();
          String assemble( const Entity &root );
          void clear();

          static String escape( const String &s );
        private:
          Vector <String> mStrings;
          Vector <Pair <Vector <Entity>, sizetype> > mLines;
          Vector <Vector <Entity> > mGroups;
          Map <RBSTree, String, String> mI18n;
          Map <RBSTree, String, Entity> mVariables;
    
          sizetype createString( const String &string );
          sizetype createLine(); // creates an empty line
          sizetype createGroup(); // creates an empty group
          void dfs( const Entity &entity, String &result, sizetype indent );
      };
    }
  }
}

