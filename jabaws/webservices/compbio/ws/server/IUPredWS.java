package compbio.ws.server;

import java.util.List;

import javax.jws.WebService;

import org.apache.log4j.Logger;

import compbio.data.msa.JABAService;
import compbio.data.msa.SequenceAnnotation;
import compbio.data.sequence.FastaSequence;
import compbio.metadata.JobSubmissionException;
import compbio.metadata.LimitExceededException;
import compbio.metadata.Preset;
import compbio.metadata.UnsupportedRuntimeException;
import compbio.metadata.WrongParameterException;
import compbio.runner.disorder.IUPred;

@WebService(endpointInterface = "compbio.data.msa.SequenceAnnotation", targetNamespace = JABAService.V2_SERVICE_NAMESPACE, serviceName = "IUPredWS")
public class IUPredWS extends SequenceAnnotationService<IUPred>
		implements
			SequenceAnnotation<IUPred> {

	private static Logger log = Logger.getLogger(IUPredWS.class);

	public IUPredWS() {
		super(new IUPred(), log);
	}

	/*
	 * No presets are supported, thus the result of this call will be as simple
	 * call to analize without parameters
	 */
	@Override
	public String presetAnalize(List<FastaSequence> sequences,
			Preset<IUPred> preset) throws UnsupportedRuntimeException,
			LimitExceededException, JobSubmissionException,
			WrongParameterException {

		return analize(sequences);
	}

}
