#ifndef JSON_BUILD_H
#define JSON_BUILD_H

#include <sstream>
#include <string>
#include <vector>

/**
 * @class JsonBuilder
 * @brief Permet de construire un JSON sous forme de chaîne.
 */
class JsonBuilder
{
public:
    /**
     * @brief Constructeur principal.
     */
    JsonBuilder()
    {
        _out << "{";
    }

    /**
     * @brief Destructeur.
     */
    ~JsonBuilder() = default;

    /**
     * @brief Débute un objet JSON associé à une clé.
     * @param key Nom du champ associé à cet objet.
     */
    void beginObject(const std::string& key);

    /**
     * @brief Termine l'objet JSON courant.
     */
    void endObject();

    /**
     * @brief Débute un tableau JSON associé à une clé.
     * @param key Nom du tableau.
     */
    void beginArray(const std::string& key = "");

    /**
     * @brief Termine le tableau JSON courant.
     */
    void endArray();

    /**
     * @brief Ajoute un champ JSON contenant un nombre (int, double, etc.).
     * @param key Nom du champ.
     * @param value Valeur numérique.
     */
    template <typename T>
    void addValue(const std::string& key, const T& value);

    /**
     * @brief Ajoute un champ JSON cotenannt un string.
     * @param key Nom du champ.
     * @param value Valeur sous forme de string.
     */
    void addString(const std::string& key, const std::string& value);

    /**
     * @brief Ajoute un bloc JSON brut sans guillemets.
     * @param key Nom du champ.
     * @param obj Contenu JSON déjà bien formé.
     */
    void addRaw(const std::string& key, const std::string& obj);

    /**
     * @brief Ajoute directement un élément JSON brut.
     * @param raw Contenu JSON.
     */
    void addRawValue(const std::string& raw);

    /**
     * @brief Génère la chaine JSON finale en fermant l'objet racine.
     * @return JSON sous forme de chaîne.
     */
    std::string build()
    {
        return _out.str() + "}";
    }

private:
    std::ostringstream _out;  ///< Flux interne utilisé pour construire progressivement le JSON
    bool _first = true;       ///< Indique s'il s'agit du premier élément dans un bloc.

    /**
     * @brief Ajoute une virgule si nécessaire avant d'insérer un nouvel élément.
     */
    void _addComma();
};

inline void JsonBuilder::beginObject(const std::string& key)
{
    _addComma();
    _out << "\"" << key << "\": {";
    _first = true;
}

inline void JsonBuilder::endObject()
{
    _out << "}";
    _first = false;
}

inline void JsonBuilder::beginArray(const std::string& key)
{
    _addComma();

    if (key.empty())
        _out << "[";
    else
        _out << "\"" << key << "\": [";

    _first = true;
}

inline void JsonBuilder::endArray()
{
    _out << "]";
    _first = false;
}

template <typename T>
inline void JsonBuilder::addValue(const std::string& key, const T& value)
{
    _addComma();
    _out << "\"" << key << "\": " << value;
}

inline void JsonBuilder::addString(const std::string& key, const std::string& value)
{
    _addComma();
    _out << "\"" << key << "\": \"" << value << "\"";
}

inline void JsonBuilder::addRaw(const std::string& key, const std::string& obj)
{
    _addComma();
    _out << "\"" << key << "\": " << obj;
}

inline void JsonBuilder::addRawValue(const std::string& raw)
{
    _addComma();
    _out << raw;
}

inline void JsonBuilder::_addComma()
{
    if (!_first)
        _out << ",";

    _first = false;
}

#endif  // JSON_BUILD_H