#include "ALittleScriptLanguageNameDecReference.h"

#include "../Index/ALittleScriptFileClass.h"
#include "../Index/ALittleScriptProjectClass.h"

ABnfGuessError ALittleScriptLanguageNameDecReference::CheckError()
{
    auto element = m_element.lock();
    if (element == nullptr) return ABnfGuessError(element, u8"节点失效");
    const auto text = element->GetElementText();
    auto* project = dynamic_cast<ALittleScriptProjectClass*>(element->GetFile()->GetProject());
    if (project != nullptr && project->GetLanguageSet().find(text) == project->GetLanguageSet().end())
        return ABnfGuessError(element, u8"不支持该目标语言");
    return nullptr;
}

bool ALittleScriptLanguageNameDecReference::QueryCompletion(const ABnfElementPtr& select, std::vector<ALanguageCompletionInfo>& list)
{
	const auto element = m_element.lock();
    if (element == nullptr) return false;

    auto* project = dynamic_cast<ALittleScriptProjectClass*>(element->GetFile()->GetProject());
    if (project == nullptr) return false;
    for (auto& name : project->GetLanguageSet())
        list.emplace_back(name, ALittleScriptIconType::LANGUAGE, "");
    return true;
}

int ALittleScriptLanguageNameDecReference::QueryClassificationTag(bool& blur)
{
    blur = false;
    return ALittleScriptColorType::CUSTOM_NAME;
}
