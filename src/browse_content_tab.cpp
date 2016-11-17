#include "browse_content_tab.h"

using namespace gui_wallet;

Browse_content_tab::Browse_content_tab()
        :
        m_synopsis_label(tr("Synopsis"))
{
    m_synopsis_layout.addWidget(&m_synopsis_label);//
    m_synopsis_layout.addWidget(&m_synopsis_text);//

    m_main_layout.addLayout(&m_synopsis_layout);
    m_main_layout.addLayout(&m_info_layout);

    setLayout(&m_main_layout);
}


Browse_content_tab::~Browse_content_tab()
{
}
