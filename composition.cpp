#include "composition.h"

#include <QXmlStreamWriter>
#include <QtXmlPatterns>
#include <QMessageBox>


Composition::Composition(fsmVector fsms, linkVector links)
     : fsms_(fsms), links_(links)
{

}

fsmVector Composition::getFsms() const
{
     return fsms_;
}

linkVector Composition::getLinks() const
{
     return links_;
}

void Composition::formXmlFile() const
{
     QFile xmlCompositionFile("composition.xml");
     xmlCompositionFile.open(QIODevice::WriteOnly);

     QXmlStreamWriter xmlWriter(&xmlCompositionFile);
     xmlWriter.setAutoFormatting(true);
     xmlWriter.writeStartDocument();

     auto isExternal = [](const Fsm& fsm)
     {
          return ( ( "" == fsm.getId() ) && ( "" == fsm.getName() ) );
     };

     auto writeFsmInfo = [&xmlWriter, &isExternal](const Fsm& fsm)
     {
          if(isExternal(fsm))
          {
               xmlWriter.writeAttribute("type", "external");
          }
          else
          {
               xmlWriter.writeAttribute("type", "internal");
               xmlWriter.writeAttribute("id_comp", fsm.getId());
          }
     };

     xmlWriter.writeStartElement("start");

     xmlWriter.writeStartElement("composition"); // <composition>
     for(const auto& fsm : fsms_)
     {
          xmlWriter.writeStartElement("FSM");
          xmlWriter.writeAttribute("name", fsm.getName());
          xmlWriter.writeAttribute("id", fsm.getId());
          xmlWriter.writeEndElement(); //</FSM>
     }
     xmlWriter.writeEndElement(); // </composition>

     xmlWriter.writeStartElement("channels");
     xmlWriter.writeAttribute("num", QString::number(links_.size()));
     for(const auto& link : links_)
     {
          xmlWriter.writeStartElement("channel"); // <channel>
          xmlWriter.writeAttribute("id", link.getId());

          xmlWriter.writeStartElement("input");
          Fsm inputFsm = link.getInputFsm();
          writeFsmInfo(inputFsm);
          xmlWriter.writeEndElement(); // </input>

          xmlWriter.writeStartElement("output");
          Fsm outputFsm = link.getOutputFsm();
          writeFsmInfo(outputFsm);
          xmlWriter.writeEndElement();

          xmlWriter.writeEndElement(); // </channel>
     }
     xmlWriter.writeEndElement();// </channels>

     xmlWriter.writeEndElement();// </start>

     xmlWriter.writeEndDocument();// XML END
     xmlCompositionFile.close();
}


