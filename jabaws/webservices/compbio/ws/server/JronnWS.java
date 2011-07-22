package compbio.ws.server;

import java.io.File;

import javax.jws.WebService;

import org.apache.log4j.Logger;

import compbio.data.msa.JABAService;
import compbio.data.msa.SequenceAnnotation;
import compbio.engine.Configurator;
import compbio.metadata.ChunkHolder;
import compbio.runner.conservation.AACon;
import compbio.runner.disorder.Jronn;

@WebService(endpointInterface = "compbio.data.msa.SequenceAnnotation", targetNamespace = JABAService.V2_SERVICE_NAMESPACE, serviceName = "JronnWS")
public class JronnWS extends SequenceAnnotationService<Jronn>
		implements
			SequenceAnnotation<Jronn> {

	private static Logger log = Logger.getLogger(JronnWS.class);

	public JronnWS() {
		super(new Jronn(), log);
	}

	@Override
	public ChunkHolder pullExecStatistics(String jobId, long position) {
		WSUtil.validateJobId(jobId);
		String file = Configurator.getWorkDirectory(jobId) + File.separator
				+ AACon.getStatFile();
		return WSUtil.pullFile(file, position);
	}

}
